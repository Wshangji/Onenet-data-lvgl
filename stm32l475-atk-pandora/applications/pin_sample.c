#include "pin_sample.h"


void led_init(void)
{
	/* ���� LED ����Ϊ���ģʽ */
  rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(LED_PIN, PIN_HIGH);
}

void led_on(void)
{
	/* LED ���� */
  rt_pin_write(LED_PIN, PIN_LOW);
}

void led_off(void)
{
	/* LED ���� */
  rt_pin_write(LED_PIN, PIN_HIGH);
}

void key_init(void)
{
	/* ���ð�������Ϊ����ģʽ */
  rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT_PULLUP);
  rt_pin_mode(PIN_KEY1, PIN_MODE_INPUT_PULLUP);
  rt_pin_mode(PIN_KEY2, PIN_MODE_INPUT_PULLUP);
  rt_pin_mode(PIN_WK_UP, PIN_MODE_INPUT_PULLDOWN);
}

void beep_init(void)
{
	/* ���÷���������Ϊ���ģʽ */
  rt_pin_mode(PIN_BEEP, PIN_MODE_OUTPUT);
}

// ������
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
