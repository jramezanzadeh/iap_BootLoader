/*
 * LedManager.cpp
 *
 *  Created on: Aug 13, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "LedManager.h"

LedManager& LedManager::instance() {
	static LedManager instance;
	return instance;
}

void LedManager::on(LED led) {
	if(led < LED_CNT)
		ledList[led].on();
}

void LedManager::off(LED led) {
	if(led < LED_CNT)
		ledList[led].off();
}

void LedManager::pulse(LED led, int time) {
	if(led < LED_CNT)
		ledList[led].pulse(time);
}

void LedManager::blink(LED led, int time) {
	if(led < LED_CNT)
		ledList[led].blink(time);
}

void LedManager::run() {
	for(int i = 0; i < LED_CNT; i++)
		ledList[i].run();
}

void LedManager::clearAll() {
	for(int i = 0; i < LED_CNT; i++)
		ledList[i].off();
}

LedManager::LedManager():ledList({{LED_CH1_GPIO_Port, LED_CH1_Pin},
		{LED_CH2_GPIO_Port, LED_CH2_Pin}, {LED_TX_GPIO_Port, LED_TX_Pin},
		{LED_ACT_GPIO_Port, LED_ACT_Pin}}) {
	// TODO Auto-generated constructor stub
	clearAll();
}

LedManager::~LedManager() {
	// TODO Auto-generated destructor stub
}

LedManager::Led::Led(GPIO_TypeDef* port, uint16_t pin):mGpioPin(port, pin) {
	mState = OFF;
	mGpioPin.setLow();
	mStartTime = 0;
	mTime = 0;
}

LedManager::Led::~Led() {
}

void LedManager::Led::on() {
	mState = ON;
	mGpioPin.setHigh();
}

void LedManager::Led::off() {
	mState = OFF;
	mGpioPin.setLow();
}

void LedManager::Led::pulse(int time) {
	mState = PULSE;
	mGpioPin.setHigh();
	mStartTime = HAL_GetTick();
	mTime = time;
}

void LedManager::Led::blink(int time) {
	mState = BLINK;
	mGpioPin.setHigh();
	mStartTime = HAL_GetTick();
	mTime = time;
}

void LedManager::Led::run() {
	switch (mState) {
	case PULSE:
		if(isTimeElapsed())
			off();
		break;
	case BLINK:
		if(isTimeElapsed()){
			mStartTime = HAL_GetTick();
			mGpioPin.toggle();
		}
		break;
	default:
		break;
	}
}

bool LedManager::Led::isTimeElapsed() {
	return (HAL_GetTick() - mStartTime > (uint32_t)mTime);
}
