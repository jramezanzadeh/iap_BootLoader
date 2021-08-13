/*
 * IoPeripheral.h
 *
 *  Created on: Apr 24, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef IOPERIPHERAL_H_
#define IOPERIPHERAL_H_

#include "stdint.h"

class IoPeripheral {
public:
	IoPeripheral();
	virtual ~IoPeripheral();

	virtual void open() = 0;
	virtual void close() = 0;
	virtual int send(uint8_t *data, int len, int timeOut = 100) = 0;
	virtual int read(uint8_t *data, int len, int timeOut = 100) = 0;
	virtual bool isReadyToSend() = 0;
};

#endif /* IOPERIPHERAL_H_ */
