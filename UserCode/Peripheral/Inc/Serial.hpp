/*
 * Serial.hpp
 *
 *  Created on: Aug 10, 2020
 *      Author: Javad Ramezanzadeh
 */

#ifndef SERIAL_HPP_
#define SERIAL_HPP_

#include "usart.h"
#include "IoPeripheral.h"

#define BUFF_LEN	512

class Serial: public IoPeripheral {
public:
	Serial(UART_HandleTypeDef *huart);
	virtual ~Serial();
	void init(USART_TypeDef *uart, int buadRate, uint32_t mode = UART_MODE_TX_RX);
	void open();
	void close();
	int send(uint8_t *data, int len, int timeOut = 100);
	int read(uint8_t *data, int len, int timeOut = 0);
	bool isReadyToSend();

private:
	UART_HandleTypeDef *mUartHandle;
	uint32_t	mMode;
	uint8_t mSerialBuff[BUFF_LEN];
	uint32_t mReadIndex;

	bool isInitialized();
	bool isRxOnly();
	bool isTxOnly();
	void readFromBuffer(uint8_t *data, int len);
	int getRecieveCount();
};

#endif /* SERIAL_HPP_ */
