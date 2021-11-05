/*
 * led_strip.cpp
 *
 *  Created on: Jun 12, 2021
 *      Author: Oğuzhan
 */

#include "led_strip.h"

LEDStrip::LEDStrip(uint8_t led_count, bool *sent_flag, TIM_HandleTypeDef *htim, uint32_t channel, int *x)
{
	this->led_count = led_count;
	this->sent_flag = sent_flag;
	this->htim = htim;
	this->channel = channel;
	this->x = x;

	set_brightness(127);
	set_single_color(0, 0, 0);
	update();
	HAL_Delay(1000);
	set_single_color(255, 255, 255);
	update();
	HAL_Delay(1000);
	set_single_color(0, 0, 0);
	update();
}

void LEDStrip::update()
{
	uint16_t index = 0;
	uint32_t color;

	for (int i = 0; i < led_count; i++)
	{
		color = ((led_data[i][GREEN] << 16) | (led_data[i][RED] << 8) | led_data[i][BLUE]);

		for (int j = 23; j >= 0; j--)
		{
			if (color & (1 << j)) pwm_data[index] = 60;
			else pwm_data[index] = 30;

			index++;
		}
	}

	*x = 50;

	for (int i = 0; i < 50; i++)
	{
		pwm_data[index] = 0;
		index++;
	}

	*x = 60;

	HAL_TIM_PWM_Start_DMA(htim, channel, (uint32_t *) pwm_data, index);

	*x = 70;

	while (!(*sent_flag)) {};
	*x = 80;
	*sent_flag = false;
	*x = 90;
}

void LEDStrip::set_brightness(uint8_t brightness)
{
	this->brightness = (float)brightness / 255;
	update_led_data();
}

void LEDStrip::set_single_color(uint8_t r, uint8_t g, uint8_t b)
{
	for (int i = 0; i < led_count; i++)
	{
		set_single_led(i, r, g, b);
	}

	update_led_data();
}

/* -------------------------------------------------- */

void LEDStrip::update_led_data()
{
	for (int i = 0; i < led_count; i++)
	{
		led_data[i][RED] = leds[i][RED] * brightness;
		led_data[i][GREEN] = leds[i][GREEN] * brightness;
		led_data[i][BLUE] = leds[i][BLUE] * brightness;
	}
}

void LEDStrip::set_single_led(uint8_t led_no, uint8_t r, uint8_t g, uint8_t b)
{
	leds[led_no][RED] = r;
	leds[led_no][GREEN] = g;
	leds[led_no][BLUE] = b;
}
