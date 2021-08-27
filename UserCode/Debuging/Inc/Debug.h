/*
 * Debug.h
 *
 *  Created on: Apr 25, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "Serial.hpp"

#define DBG_PORT_NUM 1

#define _HANDLER_PTR_(n)		&huart##n
#define HANDLER_PTR_(n)			_HANDLER_PTR_(n)

#define _UART_PTR_(n)  			USART##n
#define  UART_PTR_(n) 			_UART_PTR_(n)

#define DBG_HANDLER_PTR			(HANDLER_PTR_(DBG_PORT_NUM))
#define DBG_UART_PTR			(UART_PTR_(DBG_PORT_NUM))

#define debuger  Debug::getInstance()
#define endl "\r\n"
#define DBG_BUFF_LEN	512

class Debug {
public:

	static Debug& getInstance();
	virtual ~Debug();

	Debug& operator << (int num);
	Debug& operator << (const char *str);
	void log(const char *fmt...);
	void logHex(const char* msg, const uint8_t* buff, int len);
	void run();
	void enableBuffering();
	void flush();
private:
	Debug();
	int mReadIndex;
	int mWriteIndex;
	uint8_t mDebugBuff[DBG_BUFF_LEN];
	bool mBufferEnabeFlag;
	Serial mDebugPort;

	void write(char *data, int len);
	bool isEmpty();
	bool isBufferEnabled();
};

#endif /* DEBUG_H_ */
