/*
 * Serial.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: Javad Ramezanzadeh
 */

#include "Serial.hpp"
#include "string.h"


Serial::Serial(UART_HandleTypeDef *huart) {
	mUartHandle = huart;
	mReadIndex = 0;
	mMode = 0;
}

Serial::~Serial() {
	// TODO Auto-generated destructor stub
}

void Serial::init(USART_TypeDef *uart, int buadRate, uint32_t mode) {
	if(mUartHandle == NULL)
		return;
	if (isInitialized())
		return;
	mMode = mode;
	mUartHandle->Instance = uart;
	mUartHandle->Init.BaudRate = buadRate;
	mUartHandle->Init.WordLength = UART_WORDLENGTH_8B;
	mUartHandle->Init.StopBits = UART_STOPBITS_1;
	mUartHandle->Init.Parity = UART_PARITY_NONE;
	mUartHandle->Init.Mode = mode;
	mUartHandle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	mUartHandle->Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(mUartHandle) != HAL_OK) {
		Error_Handler();
	}
}

void Serial::open() {
	if(isTxOnly())
		return;
	HAL_UART_Receive_DMA(mUartHandle, mSerialBuff, BUFF_LEN);
}

void Serial::close() {
	HAL_UART_DeInit(mUartHandle);
}

int Serial::send(uint8_t* data, int len, int timeOut) {
	if (isRxOnly())
		return 4;
	return HAL_UART_Transmit(mUartHandle, data, len, timeOut);
}

int Serial::read(uint8_t* data, int len, int timeOut) {
	if (isTxOnly())
		return 0;
	int receivedByteCnt;
	while (1) {
		receivedByteCnt = getRecieveCount();
		if (receivedByteCnt >= len) {
			readFromBuffer(data, len);
			return len;
		} else {
			if (--timeOut < 0) {
				readFromBuffer(data, receivedByteCnt);
				return receivedByteCnt;
			}else{
				HAL_Delay(1);
			}
		}
	}
	return 0;
}

bool Serial::isInitialized() {
	return (mUartHandle->gState != HAL_UART_STATE_RESET);
}

bool Serial::isRxOnly() {
	return (mMode == UART_MODE_RX);
}

bool Serial::isTxOnly() {
	return (mMode == UART_MODE_TX);
}

void Serial::readFromBuffer(uint8_t *data, int len) {
	if (len > 0) {
		if (mReadIndex + len <= BUFF_LEN) {
			memcpy(data, mSerialBuff + mReadIndex, len);
		} else { // buffer has rolled back
			int numBytesUpToEndOfBuff = BUFF_LEN - mReadIndex;
			//first read up to end of buffer
			memcpy(data, mSerialBuff + mReadIndex, numBytesUpToEndOfBuff);
			//then read reminder from head of buffer
			memcpy(data + numBytesUpToEndOfBuff, mSerialBuff,
					len - numBytesUpToEndOfBuff);
		}
		mReadIndex += len;
		mReadIndex %= BUFF_LEN;
	}
}

bool Serial::isReadyToSend() {
	// check whether transmit empty flag is set or not
	return __HAL_UART_GET_FLAG(mUartHandle, UART_FLAG_TXE);
}

int Serial::getRecieveCount() {
	uint32_t writeIndex = BUFF_LEN - mUartHandle->hdmarx->Instance->NDTR;
	return ((writeIndex - mReadIndex) % BUFF_LEN);
}
