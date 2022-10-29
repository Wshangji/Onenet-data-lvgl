
//该头文件含 sample_04_aht10_read_data.c 中的 API
#include <sample_read_data.h>

#include <dfs_posix.h>

#define DBG_SECTION_NAME     "data_store"
#define DBG_LEVEL            DBG_INFO
#include <rtdbg.h>

#define FILE_PATH  "/sensor_data.txt"

static char buf[100];

void data_store_entry(void *parameter)
{
    rt_uint32_t e;
    rt_event_t event;
    int fd = -1, size;
    struct rt_sensor_data humi_data, temp_data;
    rt_size_t res;
    int num = 10;

    /*  根据名称查找event对象 */
    event = (rt_event_t)rt_object_find(INFORM_EVENT_NAME, RT_Object_Class_Event);


    // 创建一个新的文件，打开
    fd = open(FILE_PATH, O_WRONLY | O_CREAT | O_APPEND);
    if (fd < 0)
    {
        LOG_E("open file failed!");
        goto __exit;
    }

    while (num--)
    {
        /* 永久等待事件，获取到之后清除事件并将数据存入文件 */
        if (rt_event_recv(event, INFORM_FLAG_STORE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &e) == RT_EOK)
        {
            humi_get_data(&humi_data);
            temp_get_data(&temp_data);
            
            /* 按照下面的格式进行存储 */
            sprintf(buf, "humi:%3d.%d%%, timestamp:%5d, temp:%3d.%dC, timestamp:%5d\r\n",
                    humi_data.data.humi / 10, humi_data.data.humi % 10, humi_data.timestamp,
                    temp_data.data.temp / 10, temp_data.data.temp % 10, temp_data.timestamp);
            
            size = strlen(buf);
            
            /* 写入文件 */
            res = write(fd, buf, size);
            if (res != size)
            {
                LOG_W("write data failed, res:%d", res);
            }
        }
    }

__exit:
    if (fd >= 0)
        close(fd);
}

int data_store_init(void)
{
    rt_thread_t tid;

    /* 创建一个线程完成 */
    tid = rt_thread_create("data_store", data_store_entry, RT_NULL, 1024, 20, 5);
    
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    return 0;
}
