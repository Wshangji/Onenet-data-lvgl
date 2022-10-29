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

/* ���ɿ����������ú� */
/* һ��RGB565ͼƬռ�õĻ����С */
#define PIC_SIZE 115200
/* LCD��ʾ����ʼX���� */
#define DISPLAY_START_X 0
/* LCD��ʾ����ʼY���� */
#define DISPLAY_START_Y 80
/* LCD��ȷֱ��� */
#define LCD_WIDTH   240
/* LCD�߶ȷֱ��� */
#define LCD_HEIGHT  80

//int sd_play_part_video()
//{
//		lcd_clear(0x0000);
//    int fd = -1;
//    int length;
//		int offset;     /* �ļ�λ��ƫ�� */
//    fd = open("harmonyos.bin", O_RDONLY);
//    uint8_t *buffer = NULL;
//    buffer = rt_malloc(LCD_WIDTH * LCD_HEIGHT * 2);//�������ݻ�����
//		if (fd)
//		{
//			for (int j = 0; j < 70; j++)
//			{
//			/* 5.��ƫ������ӣ��Ƶ��仯���� */
//      offset += LCD_WIDTH * LCD_HEIGHT * 2;
//			//�ļ�ƫ�ƣ��Զ�ȡ��һ������
//      lseek(fd,offset);
//      length = read(fd, buffer,LCD_WIDTH * LCD_HEIGHT * 2);
//      lcd_show_image(DISPLAY_START_X, DISPLAY_START_Y, LCD_WIDTH, LCD_HEIGHT,buffer);
//			}
//		}
//		return RT_EOK;
//}


static int lcd_sample(void)
{
    /* ���� */
    lcd_clear(WHITE);

    /* ��ʾ RT-Thread logo */
    lcd_show_image(0, 0, 240, 69, image_rttlogo);
    
    /* ���ñ���ɫ��ǰ��ɫ */
    lcd_set_color(WHITE, BLACK);

    /* �� LCD ����ʾ�ַ� */
    lcd_show_string(10, 69, 16, "Hello,Hum and Temp!");
    lcd_show_string(10, 69+16, 24, "Nanf_bunan");
    lcd_show_string(10, 69+16+24, 32, "RT-Thread");
    
    /* �� LCD �ϻ��� */
    lcd_draw_line(0, 69+16+24+32, 240, 69+16+24+32);
    
    /* �� LCD �ϻ�һ��ͬ��Բ */
    lcd_draw_point(120, 194);
    for (int i = 0; i < 46; i += 4)
    {
        lcd_draw_circle(120, 194, i);
    }
    
    return RT_EOK;
}
INIT_APP_EXPORT(lcd_sample);
#endif /* BSP_USING_SPI_LCD */
