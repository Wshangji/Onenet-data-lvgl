/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-08-28     WillianChan   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_fs.h>

#ifdef BSP_USING_SPI_LCD
#include <drv_lcd.h>
#include <rttlogo.h>

/* 鸿蒙开机界面设置宏 */
/* 一张RGB565图片占用的缓存大小 */
#define PIC_SIZE 115200
/* LCD显示的起始X坐标 */
#define DISPLAY_START_X 0
/* LCD显示的起始Y坐标 */
#define DISPLAY_START_Y 80
/* LCD宽度分辨率 */
#define LCD_WIDTH   240
/* LCD高度分辨率 */
#define LCD_HEIGHT  80

//int sd_play_part_video()
//{
//		lcd_clear(0x0000);
//    int fd = -1;
//    int length;
//		int offset;     /* 文件位置偏移 */
//    fd = open("harmonyos.bin", O_RDONLY);
//    uint8_t *buffer = NULL;
//    buffer = rt_malloc(LCD_WIDTH * LCD_HEIGHT * 2);//创建数据缓冲区
//		if (fd)
//		{
//			for (int j = 0; j < 70; j++)
//			{
//			/* 5.将偏移往后加，移到变化区域 */
//      offset += LCD_WIDTH * LCD_HEIGHT * 2;
//			//文件偏移，以读取下一段数据
//      lseek(fd,offset);
//      length = read(fd, buffer,LCD_WIDTH * LCD_HEIGHT * 2);
//      lcd_show_image(DISPLAY_START_X, DISPLAY_START_Y, LCD_WIDTH, LCD_HEIGHT,buffer);
//			}
//		}
//		return RT_EOK;
//}


static int lcd_sample(void)
{
    /* 清屏 */
    lcd_clear(WHITE);

    /* 显示 RT-Thread logo */
    lcd_show_image(0, 0, 240, 69, image_rttlogo);
    
    /* 设置背景色和前景色 */
    lcd_set_color(WHITE, BLACK);

    /* 在 LCD 上显示字符 */
    lcd_show_string(10, 69, 16, "Hello,Hum and Temp!");
    lcd_show_string(10, 69+16, 24, "Nanf_bunan");
    lcd_show_string(10, 69+16+24, 32, "RT-Thread");
    
    /* 在 LCD 上画线 */
    lcd_draw_line(0, 69+16+24+32, 240, 69+16+24+32);
    
    /* 在 LCD 上画一个同心圆 */
    lcd_draw_point(120, 194);
    for (int i = 0; i < 46; i += 4)
    {
        lcd_draw_circle(120, 194, i);
    }
    
    return RT_EOK;
}
INIT_APP_EXPORT(lcd_sample);
#endif /* BSP_USING_SPI_LCD */
