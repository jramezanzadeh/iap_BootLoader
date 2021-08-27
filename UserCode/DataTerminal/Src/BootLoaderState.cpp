/*
 * BootLoaderState.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "BootLoaderState.h"
#include "LedManager.h"
#include "FlashOperation.h"
#include "Debug.h"

BootLoaderState::BootLoaderState(DataTerminal* ctx) {
	// TODO Auto-generated constructor stub
	mCTX = ctx;
}

BootLoaderState::~BootLoaderState() {
	// TODO Auto-generated destructor stub
}

void BootLoaderState::sendNack() {
	ledManager.pulse(LedManager::CH2, 100);
	flash.lock();
	debuger << "NACK" << endl;
	//TODO: should be set or not?
	//mCTX->setDowloadingApp(false);
	mCTX->writeByte(NACK);
}

void BootLoaderState::sendAck() {
	ledManager.pulse(LedManager::CH1, 100);
	mCTX->writeByte(ACK);
}
