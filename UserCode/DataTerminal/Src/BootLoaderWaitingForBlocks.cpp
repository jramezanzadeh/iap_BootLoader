/*
 * BootLoaderWaitingForBlocks.cpp
 *
 *  Created on: Aug 20, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "BootLoaderWaitingForBlocks.h"
#include "BootLoaderIdleState.h"
#include "LedManager.h"
#include "Debug.h"

BootLoaderWaitingForBlocks::BootLoaderWaitingForBlocks(DataTerminal *ctx):
BootLoaderState(ctx), mMetaData(mCTX->getMetaData()){
	// TODO Auto-generated constructor stub
	mTotalByteCnt = 0;
	mIntegrityCalculator.reset();
	mWriteAddress = flash.getAppAddress();

}

BootLoaderWaitingForBlocks::~BootLoaderWaitingForBlocks() {
	// TODO Auto-generated destructor stub
}

void BootLoaderWaitingForBlocks::handleReceivedByte(uint8_t byte) {
	mIntegrityCalculator.update((char*) &byte, 1);

	int idx = mTotalByteCnt % FLASH_PAGE_SIZE;
	mCurrentPage[idx] = byte;
	mTotalByteCnt++;

	if(isEndOfBlock()) {
		flash.writePage(mCurrentPage, mWriteAddress);
		mWriteAddress += FLASH_PAGE_SIZE;
		memset(mCurrentPage, 0, sizeof mCurrentPage);

		debuger.log("Sending ACK, blk[%d]\r\n", mTotalByteCnt/FLASH_PAGE_SIZE);
		sendAck();
	}
	//end of downloading app
	if (mTotalByteCnt == mMetaData.getAppSize()) {
		if (!isEndOfBlock()) {
			// We have a partial page to write
			flash.writePage(mCurrentPage, mWriteAddress);
			debuger << "Sending ACK(last blk)" << endl;
			sendAck();
		}

		debuger.log("Received %d bytes\r\n", mTotalByteCnt);

		uint8_t appIntegrity[8];
		mIntegrityCalculator.finalaize(appIntegrity);
		debuger.logHex("calc integrity:", appIntegrity, 8);
		if (memcmp(appIntegrity, mMetaData.getAppIntegrityChk(), 8)) {
			debuger << "MD5 mismatch :(" << endl;
			sendNack();

		} else {
			// Good transfer
			debuger << "MD5 match :)" << endl;
			debuger << "Sending ACK(verification)" << endl;
			sendAck();
			// write meta data to flash
			flash.writeAppMetaData(mMetaData);
			flash.lock();
			/*Download done, flush dataTerminal and debug buffers and then reset*/
			mCTX->flush();
			debuger.flush();
			NVIC_SystemReset();
		}
		mCTX->setStateTo(new BootLoaderIdleState(mCTX));
	}
}

bool BootLoaderWaitingForBlocks::isEndOfBlock() {
	return (mTotalByteCnt % FLASH_PAGE_SIZE == 0);
}
