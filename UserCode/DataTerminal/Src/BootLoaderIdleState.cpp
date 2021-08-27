/*
 * BootLoaderIdleState.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "BootLoaderIdleState.h"
#include "Debug.h"
#include "LedManager.h"
#include "BootLoaderWaitingForHeaderState.h"

BootLoaderIdleState::BootLoaderIdleState(DataTerminal* ctx):BootLoaderState(ctx) {
	// TODO Auto-generated constructor stub

}

BootLoaderIdleState::~BootLoaderIdleState() {
	// TODO Auto-generated destructor stub
}

void BootLoaderIdleState::handleReceivedByte(uint8_t byte) {
	if (byte == START_TRANSFER_CMD) {
		debuger << "Sending ACK(start)" << endl;
		sendAck();
		mCTX->setDowloadingApp(true);
		mCTX->setStateTo(new BootLoaderWaitingForHeaderState(mCTX));
	} else {
		debuger.log("Bad command: %0.2X\r\n", byte);
		sendNack();
	}
}
