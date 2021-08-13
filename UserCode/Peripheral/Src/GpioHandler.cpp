/*
 * GpioHandler.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <GpioHandler.h>

GpioHandler::GpioHandler(GPIO_TypeDef* port, uint16_t pin) {
	// TODO Auto-generated constructor stub
	mPort = port;
	mPin = pin;
	//init();
}


GpioHandler::~GpioHandler() {
	// TODO Auto-generated destructor stub
}

void GpioHandler::init(uint32_t mode, uint32_t pull, uint32_t speed) {
	//TODO: enable Port clock
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(mode == GPIO_MODE_OUTPUT_PP)
		HAL_GPIO_WritePin(mPort, mPin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = mPin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = speed;
	HAL_GPIO_Init(mPort, &GPIO_InitStruct);
}

void GpioHandler::setHigh() {
	HAL_GPIO_WritePin(mPort, mPin, GPIO_PIN_SET);
}

void GpioHandler::setLow() {
	HAL_GPIO_WritePin(mPort, mPin, GPIO_PIN_RESET);
}

bool GpioHandler::read() {
	return (HAL_GPIO_ReadPin(mPort, mPin) == GPIO_PIN_SET);
}

void GpioHandler::toggle() {
	HAL_GPIO_TogglePin(mPort, mPin);
}
