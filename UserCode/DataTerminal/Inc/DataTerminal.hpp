/*
 * Terminal.hpp
 *
 *  Created on: Jul 18, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef DATATERMINAL_HPP_
#define DATATERMINAL_HPP_

#include "CompileOptions.hpp"
#ifdef ENABLE_TERMINAL

#include "Serial.hpp"
#include "AppMetaData.h"

#define dataTerminal DataTerminal::instance()
#define TERM_BUFF_LEN 512

using namespace std;
class BootLoaderState;

class DataTerminal
{
public:
	static DataTerminal& instance();

	void init();
	void run();
	void writeByte(uint8_t byte);
	void setStateTo(BootLoaderState* state);

	bool isDowloadingApp() const {
		return mDownloadingApp;
	}

	void setDowloadingApp(bool dowloadingApp) {
		mDownloadingApp = dowloadingApp;
	}

	AppMetaData& getMetaData() {
		return mMetaData;
	}
	void flush();

private:
	int mReadIndex;
	int mWriteIndex;
	uint8_t mTxBuff[TERM_BUFF_LEN];
	Serial 	mTermPort;
	bool 	mDownloadingApp;
	BootLoaderState* 	mCurrentState;
	AppMetaData			mMetaData;

	DataTerminal();
	bool isTxBuffEmpty();
	void processCharacter(char c);
};
#endif

#endif /* DATATERMINAL_HPP_ */
