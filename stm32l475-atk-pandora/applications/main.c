/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <onenet.h>
#include <sample_read_data.h>

extern int data_store_init(void);
int main(void)
{   
    //数据存储
    collection_init();
    data_store_init();
		//接受控制命令
		onenet_set_cmd_rsp();
		rt_thread_delay(1000);
		//循环上传数据
		onenet_upload_cycle();
    return RT_EOK;
}
