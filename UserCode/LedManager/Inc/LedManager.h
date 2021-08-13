/*
 * LedManager.h
 *
 *  Created on: Aug 13, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef LEDMANAGER_LEDMANAGER_H_
#define LEDMANAGER_LEDMANAGER_H_

#include "GpioHandler.h"

#define ledManager LedManager::instance()

class LedManager {
public:
	enum LED{
		CH1 = 0,
		CH2,
		TX,
		ACT,
		LED_CNT
	};
	static LedManager& instance();
	virtual ~LedManager();
	void on(LED led);
	void off(LED led);
	void pulse(LED led, int time);
	void blink(LED led, int time);
	void clearAll();
	void run();

private:

	class Led{
	public:
		Led(GPIO_TypeDef* port, uint16_t pin);
		virtual ~Led();
		void on();
		void off();
		void pulse(int time);
		void blink(int time);
		void run();
	private:
		enum State{
			ON = 0,
			OFF,
			PULSE,
			BLINK,
		};
		GpioHandler mGpioPin;
		State mState;
		uint32_t mStartTime;
		int mTime;

		bool isTimeElapsed();
	};

	Led ledList[LED_CNT];
	LedManager();

};

#endif /* LEDMANAGER_LEDMANAGER_H_ */
