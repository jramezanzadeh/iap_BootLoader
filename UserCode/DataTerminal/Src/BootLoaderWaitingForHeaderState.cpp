/*
 * BootLoaderWaitingForHeaderState.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "BootLoaderWaitingForHeaderState.h"
#include "BootLoaderWaitingForBlocks.h"
#include "BootLoaderIdleState.h"
#include "Debug.h"
#include "FlashOperation.h"
#include "LedManager.h"

BootLoaderWaitingForHeaderState::BootLoaderWaitingForHeaderState(DataTerminal *ctx):
BootLoaderState(ctx), mMetaData(mCTX->getMetaData()) {
	// TODO Auto-generated constructor stub
	mBytesToRecieve = mMetaData.getByteCount();
	mByteIdx = 0;
	mTmpBuff = new uint8_t[mBytesToRecieve];
}

BootLoaderWaitingForHeaderState::~BootLoaderWaitingForHeaderState() {
	// TODO Auto-generated destructor stub
	delete[] mTmpBuff;
}

void BootLoaderWaitingForHeaderState::handleReceivedByte(uint8_t byte) {

	mTmpBuff[mByteIdx++] = byte;
	if (mByteIdx == mBytesToRecieve) {
		mMetaData.fromArray(mTmpBuff);
		debuger.log("Magic: %0.8x\r\n", mMetaData.getMagic());
		mMetaData.fromArray(mTmpBuff);
		// Is the metadata same?
		if (mMetaData.getMagic() == METADATA_MAGIC) {

			debuger.log("App Size: %d bytes\r\n", mMetaData.getAppSize());
			debuger.logHex("Integrity Check:", mMetaData.getAppIntegrityChk(), 8);
			flash.unlock();
			debuger << "Sending ACK(header)" << endl;
			sendAck();
			mCTX->setStateTo(new BootLoaderWaitingForBlocks(mCTX));
		} else {
			debuger << "Bad MetaData" << endl;
			sendNack();
			mCTX->setStateTo(new BootLoaderIdleState(mCTX));
		}
	}
}
