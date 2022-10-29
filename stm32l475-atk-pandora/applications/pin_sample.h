/*
 * Copyright (c) 2022, Developer Nanf_buanan
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-10-10    Nanf_bunan        the first version
 */

#ifndef __PIN_SAMPLE_H__
#define __PIN_SAMPLE_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* 配置 LED 灯引脚 */
#define LED_PIN    GET_PIN(E, 7)
/* 配置 蜂鸣器 引脚 */
#define PIN_BEEP   GET_PIN(B, 2)      // PB2 :  BEEP         --> BEEP
/* 配置 按键 引脚 */
#define PIN_KEY0   GET_PIN(D, 8)      // PD8 :  KEY0         --> KEY
#define PIN_KEY1   GET_PIN(D, 9)      // PD9 :  KEY1         --> KEY
#define PIN_KEY2   GET_PIN(D, 10)     // PD10:  KEY2         --> KEY
#define PIN_WK_UP  GET_PIN(D, 11)     // PD11:  WK_UP        --> KEY

/* led初始化 */
void led_init(void);
void led_on(void);
void led_off(void);
/* 按键初始化 */
void key_init(void);
/* 蜂鸣器初始化 */
void beep_init(void);
/* 蜂鸣器控制 */
void beep_ctrl(rt_uint8_t on);
/* 硬件初始化 */
int hardware_init(void);

#endif
