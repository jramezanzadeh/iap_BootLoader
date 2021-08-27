/*
 * BootLoaderWaitingForHeaderState.h
 *
 *  Created on: Aug 19, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef DATATERMINAL_BOOTLOADERWAITINGFORHEADERSTATE_H_
#define DATATERMINAL_BOOTLOADERWAITINGFORHEADERSTATE_H_

#include <BootLoaderState.h>
#include <AppMetaData.h>

class BootLoaderWaitingForHeaderState: public BootLoaderState {
public:
	BootLoaderWaitingForHeaderState(DataTerminal *ctx);
	virtual ~BootLoaderWaitingForHeaderState();

	void handleReceivedByte(uint8_t byte);

private:
	uint32_t mBytesToRecieve;
	uint32_t mByteIdx;
	uint8_t *mTmpBuff;
	AppMetaData& mMetaData;
};

#endif /* DATATERMINAL_BOOTLOADERWAITINGFORHEADERSTATE_H_ */
