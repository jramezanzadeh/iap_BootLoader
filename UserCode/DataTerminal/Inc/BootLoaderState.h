/*
 * BootLoaderState.h
 *
 *  Created on: Aug 19, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef DATATERMINAL_BOOTLOADERSTATE_H_
#define DATATERMINAL_BOOTLOADERSTATE_H_

#include "stdint.h"
#include "DataTerminal.hpp"

#define ACK     				(uint8_t)0x05
#define NACK    				(uint8_t)0x06

#define START_TRANSFER_CMD      0xD4
#define START_BLOCK_CMD         0xD6

class BootLoaderState {
public:
	BootLoaderState(DataTerminal* ctx);
	virtual ~BootLoaderState();

	virtual void handleReceivedByte(uint8_t byte) = 0;
protected:
	DataTerminal* mCTX;
	void sendNack();
	void sendAck();
};

#endif /* DATATERMINAL_BOOTLOADERSTATE_H_ */
