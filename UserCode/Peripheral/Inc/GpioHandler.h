/*
 * GpioHandler.h
 *
 *  Created on: Apr 24, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef GPIOHANDLER_H_
#define GPIOHANDLER_H_

#include "gpio.h"

class GpioHandler {
public:
	GpioHandler(GPIO_TypeDef* port, uint16_t pin);
	virtual ~GpioHandler();
	void init(uint32_t mode = GPIO_MODE_INPUT,
			uint32_t pull = GPIO_NOPULL,
			uint32_t speed = GPIO_SPEED_FREQ_LOW);
	void setHigh();
	void setLow();
	bool read();
	void toggle();

private:
	GPIO_TypeDef 	*mPort;
	uint16_t		mPin;

};

#endif /* GPIOHANDLER_H_ */
