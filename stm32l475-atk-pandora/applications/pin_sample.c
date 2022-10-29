#include "pin_sample.h"


void led_init(void)
{
	/* 设置 LED 引脚为输出模式 */
  rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(LED_PIN, PIN_HIGH);
}

void led_on(void)
{
	/* LED 灯亮 */
  rt_pin_write(LED_PIN, PIN_LOW);
}

void led_off(void)
{
	/* LED 灯灭 */
  rt_pin_write(LED_PIN, PIN_HIGH);
}

void key_init(void)
{
	/* 设置按键引脚为输入模式 */
  rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT_PULLUP);
  rt_pin_mode(PIN_KEY1, PIN_MODE_INPUT_PULLUP);
  rt_pin_mode(PIN_KEY2, PIN_MODE_INPUT_PULLUP);
  rt_pin_mode(PIN_WK_UP, PIN_MODE_INPUT_PULLDOWN);
}

void beep_init(void)
{
	/* 设置蜂鸣器引脚为输出模式 */
  rt_pin_mode(PIN_BEEP, PIN_MODE_OUTPUT);
}

// 蜂鸣器
void beep_ctrl(rt_uint8_t on)
{
    if (on)
    {
        rt_pin_write(PIN_BEEP, PIN_HIGH);
    }
    else
    {
        rt_pin_write(PIN_BEEP, PIN_LOW);
    }
}

int hardware_init(void)
{
	led_init();
	key_init();
	beep_init();
	return RT_EOK;
}

INIT_APP_EXPORT(hardware_init);
