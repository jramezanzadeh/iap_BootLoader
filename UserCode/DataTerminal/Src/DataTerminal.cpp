/*
 * Terminal.cpp
 *
 *  Created on: Jul 18, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "DataTerminal.hpp"
#include "stm32f4xx.h"
#include "Debug.h"
#include <stdio.h>
#include <cstring>
#include "usart.h"
#include "LEDManager.h"

#ifdef ENABLE_TERMINAL

DataTerminal& DataTerminal::instance() {
	static DataTerminal __instance;
	return __instance;
}

DataTerminal::DataTerminal() :
						mTermPort(&huart6) {
	mReadIndex = 0;
	mWriteIndex = 0;
}

void DataTerminal::init() {
	mTermPort.init(USART6, 115200, UART_MODE_TX_RX);
	mTermPort.open();
}

void DataTerminal::processCharacter(char c) {

}

void DataTerminal::run() {
	uint8_t byte;
	// handle rx
	if (mTermPort.read(&byte, 1, 0) > 0) {
		processCharacter(byte);
	}
	// handle tx
	if (mTermPort.isReadyToSend()) {
		if (!isTxBuffEmpty()) {
			mTermPort.send(mTxBuff + mReadIndex, 1, 0);// TX is ready, so it isn't needed to wait
			mReadIndex++;
			mReadIndex %= TERM_BUFF_LEN;
		}
	}
}

bool DataTerminal::isTxBuffEmpty() {
	return (mReadIndex == mWriteIndex);
}

void DataTerminal::writeByte(uint8_t byte) {
	mTxBuff[mWriteIndex++] = byte;
	mWriteIndex %= TERM_BUFF_LEN;
}

#endif

