/*
 * Debug.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <Debug.h>
#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

Debug& Debug::getInstance() {
	static Debug instance;
	return instance;
}

Debug& Debug::operator <<(int num) {
	char tmpStr[20];
	sprintf(tmpStr, " %d", num);
	write(tmpStr, strlen(tmpStr));
	return *this;
}

Debug& Debug::operator <<(const char* str) {
	write((char*)str, strlen(str));
	return *this;
}

void Debug::log(const char* fmt...) {
	char tmpStr[100];
	va_list args;
	va_start(args, fmt);
	int RetLen = vsnprintf(tmpStr, 100, fmt, args);
	if(RetLen < 100)
		write(tmpStr, RetLen);
	else{
		operator <<("error in writing log\r\n");
	}
	va_end(args);
}

Debug::Debug():mDebugPort(DBG_HANDLER_PTR) {
	// TODO Auto-generated constructor stub
	mReadIndex = 0;
	mWriteIndex = 0;
	mBufferEnabeFlag = false;
	mDebugPort.init(DBG_UART_PTR, 115200, UART_MODE_TX);
	mDebugPort.open();
}

Debug::~Debug() {
	// TODO Auto-generated destructor stub
}

void Debug::write(char* data, int len) {
	if (isBufferEnabled()) {
		for (int idx = 0; idx < len; idx++) {
			mDebugBuff[mWriteIndex++] = data[idx];
			mWriteIndex %= DBG_BUFF_LEN;
		}
	} else
		mDebugPort.send((uint8_t*) data, len, HAL_MAX_DELAY);
}

bool Debug::isEmpty() {
	return (mReadIndex == mWriteIndex);
}

void Debug::run() {
	if (mDebugPort.isReadyToSend()) {
		if (!isEmpty()) {
			mDebugPort.send(mDebugBuff + mReadIndex, 1, 0);
			mReadIndex++;
			mReadIndex %= DBG_BUFF_LEN;
		}
	}
}

void Debug::enableBuffering() {
	mBufferEnabeFlag = true;
}

bool Debug::isBufferEnabled() {
	return mBufferEnabeFlag;
}

void Debug::logHex(const char* msg, const uint8_t* buff, int len) {
	log("%s", msg);
	for(int i = 0; i < len; i++)
		log("%0.02X ", buff[i]);
	log(endl);
}
//TODO: this is copy of flush function in DataTerminal, it is suffering
void Debug::flush() {
	while(!isEmpty()){
		mDebugPort.send(mDebugBuff + mReadIndex, 1, 10);
		mReadIndex++;
		mReadIndex %= DBG_BUFF_LEN;
	}
}
