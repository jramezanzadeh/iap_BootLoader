/*
 * BootLoaderIdleState.h
 *
 *  Created on: Aug 19, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef DATATERMINAL_BOOTLOADERIDLESTATE_H_
#define DATATERMINAL_BOOTLOADERIDLESTATE_H_

#include <BootLoaderState.h>

class BootLoaderIdleState: public BootLoaderState {
public:
	BootLoaderIdleState(DataTerminal* ctx);
	virtual ~BootLoaderIdleState();

	void handleReceivedByte(uint8_t byte);
};

#endif /* DATATERMINAL_BOOTLOADERIDLESTATE_H_ */
