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

#define TERM_BUFF_LEN 512
using namespace std;

class DataTerminal
{
public:
    static DataTerminal& instance();

    void init();
    void run();
    void writeByte(uint8_t byte);

private:
    DataTerminal();
    bool isTxBuffEmpty();
    void processCharacter(char c);
private:
    int mReadIndex;
	int mWriteIndex;
	uint8_t mTxBuff[TERM_BUFF_LEN];
	Serial mTermPort;
};
#endif

#endif /* DATATERMINAL_HPP_ */
