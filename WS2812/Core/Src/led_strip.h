/*
 * led_strip.h
 *
 *  Created on: Jun 12, 2021
 *      Author: Oğuzhan
 */

#ifndef SRC_LED_STRIP_H_
#define SRC_LED_STRIP_H_

#include "stm32f4xx_hal.h"

#define RED 1
#define GREEN 2
#define BLUE 3

#define MAX_COUNT 256
#define END_COUNT 50
#define DATA_LENGTH 24

class LEDStrip
{
public:
	LEDStrip(uint8_t led_count, bool *sent_flag, TIM_HandleTypeDef *htim, uint32_t channel, int *x);

	void update();
	void set_brightness(uint8_t brightness);
	void set_single_color(uint8_t r, uint8_t g, uint8_t b);

private:
	uint8_t leds[MAX_COUNT][3];
	uint8_t led_data[MAX_COUNT][3];
	uint16_t pwm_data[DATA_LENGTH * MAX_COUNT + END_COUNT];

	uint8_t led_count;
	float brightness;
	bool *sent_flag;
	TIM_HandleTypeDef *htim;
	uint32_t channel;
	int *x;

	void update_led_data();
	void set_single_led(uint8_t led_no, uint8_t r, uint8_t g, uint8_t b);
};


#endif /* SRC_LED_STRIP_H_ */
