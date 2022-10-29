
#include <sample_read_data.h>     //含 sample_04_aht10_read_data.c 中的 API

//该文件是基于 sample_aht10_r.c 修改的，都是获取温湿度传感器的数据
#include <rtthread.h>
#include <rthw.h>

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <sensor.h>

#define DBG_SECTION_NAME     "read_data"
#define DBG_LEVEL            DBG_INFO
#include <rtdbg.h>

#define HUMI_DEV_NAME   "humi_aht"
#define TEMP_DEV_NAME   "temp_aht"

static rt_event_t event;
static struct rt_sensor_data humi_data, temp_data;

void sensor_data_poll(void *parameter)
{
    rt_device_t humi_dev, temp_dev = RT_NULL;
    rt_size_t res;

    /* ө֒ςʪ׈ԫِǷʨѸ */
    humi_dev = rt_device_find(HUMI_DEV_NAME);
    temp_dev = rt_device_find(TEMP_DEV_NAME);
    if (humi_dev == RT_NULL || temp_dev == RT_NULL)
    {
        LOG_E("Find device faied");
        goto __exit;
    }

    if (rt_device_open(humi_dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK
            || rt_device_open(temp_dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        LOG_E("open device failed!");
        goto __exit;
    }

    /* ʨ׃ԫِǷʨѸ˽ߝˤԶ̙ÊΪ 100HZ */
    rt_device_control(humi_dev, RT_SENSOR_CTRL_SET_ODR, (void *)100);
    rt_device_control(temp_dev, RT_SENSOR_CTRL_SET_ODR, (void *)100);

    while (1)
    {
        res = rt_device_read(humi_dev, 0, &humi_data, 1);
        if (res != 1)
        {
            LOG_E("read humi data failed!");
        }
        res = rt_device_read(temp_dev, 0, &temp_data, 1);
        if (res != 1)
        {
            LOG_E("read temp data failed!");
        }

        LOG_D("temp:%3d.%dC, timestamp:%5d", temp_data.data.temp / 10, temp_data.data.temp % 10, temp_data.timestamp);
        LOG_D("humi:%3d.%d%%, timestamp:%5d", humi_data.data.humi / 10, humi_data.data.humi % 10, humi_data.timestamp);
        
        rt_event_send(event, INFORM_FLAG_STORE);
        
        rt_thread_mdelay(100);
    }

__exit:
    if (humi_dev)
        rt_device_close(humi_dev);
    if (temp_dev)
        rt_device_close(temp_dev);
}

int temp_get_data(struct rt_sensor_data *data)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    *data = temp_data;

    rt_hw_interrupt_enable(level);
    return 0;
}

int humi_get_data(struct rt_sensor_data *data)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    *data = humi_data;

    rt_hw_interrupt_enable(level);
    return 0;
}

int collection_init(void)
{
    rt_thread_t tid = RT_NULL;
    
    event = rt_event_create(INFORM_EVENT_NAME, RT_IPC_FLAG_FIFO);
    if (event == RT_NULL)
    {
        LOG_E("create event failed!");
    }

    tid = rt_thread_create("sen_poll", sensor_data_poll, RT_NULL, 1024, 20, 5);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
