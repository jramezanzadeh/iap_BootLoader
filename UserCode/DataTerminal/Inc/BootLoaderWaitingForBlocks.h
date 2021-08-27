/*
 * BootLoaderWaitingForBlocks.h
 *
 *  Created on: Aug 20, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef DATATERMINAL_BOOTLOADERWAITINGFORBLOCKS_H_
#define DATATERMINAL_BOOTLOADERWAITINGFORBLOCKS_H_

#include <BootLoaderState.h>
#include "IntegrityCalc.h"
#include "FlashOperation.h"
#include "AppMetaData.h"

class BootLoaderWaitingForBlocks: public BootLoaderState {
public:
	BootLoaderWaitingForBlocks(DataTerminal *ctx);
	virtual ~BootLoaderWaitingForBlocks();

	void handleReceivedByte(uint8_t byte);

private:
	uint32_t		mTotalByteCnt;
	IntegrityCalc 	mIntegrityCalculator;
	uint8_t 		mCurrentPage[FLASH_PAGE_SIZE];
	uint32_t 		mWriteAddress;
	AppMetaData&	mMetaData;

	bool isEndOfBlock();


};

#endif /* DATATERMINAL_BOOTLOADERWAITINGFORBLOCKS_H_ */
