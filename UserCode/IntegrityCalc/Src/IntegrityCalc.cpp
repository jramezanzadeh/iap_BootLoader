/*
 * IntegrityCheck.cpp
 *
 *  Created on: Aug 14, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <IntegrityCalc.h>
#include "string.h"

IntegrityCalc::IntegrityCalc() {
	// TODO Auto-generated constructor stub
	key1[0] = 0xAC; key1[1] = 0x16;
	key1[2] = 0x9A; key1[3] = 0x3B;
	key1[4] = 0xE7; key1[5] = 0xFC;
	key1[6] = 0xC2; key1[7] = 0xEC;

	key2[0] = 0xD8; key2[1] = 0x5F;
	key2[2] = 0x17; key2[3] = 0x28;
	key2[4] = 0xF7; key2[5] = 0x7F;
	key2[6] = 0x8D; key2[7] = 0xCA;
	reset();
}

IntegrityCalc::~IntegrityCalc() {
	// TODO Auto-generated destructor stub
}

void IntegrityCalc::reset() {

	mac[0] = 0xA1; mac[1] = 0xBF;
	mac[2] = 0xC2; mac[3] = 0x89;
	mac[4] = 0xEB; mac[5] = 0x77;
	mac[6] = 0x00; mac[7] = 0xAD;
}

void IntegrityCalc::update(char* data, int len) {

	for (int i = 0; i < len; i++) {
		mac[0] = key1[0] * data[i] + key1[1] * mac[3] + key1[7] * 3  + (mac[0] ^ data[i]);
		mac[1] = key1[1] * data[i] + key1[2] * mac[2] + key1[6] * 5  + (mac[1] ^ data[i]);
		mac[2] = key1[2] * data[i] + key1[3] * mac[1] + key1[5] * 7  + (mac[2] ^ data[i]);
		mac[3] = key1[3] * data[i] + key1[0] * mac[0] + key1[4] * 11 + (mac[3] ^ data[i]);
		mac[4] = key2[0] * data[i] + key2[1] * mac[7] + key2[7] * 13 + (mac[4] ^ data[i]);
		mac[5] = key2[1] * data[i] + key2[2] * mac[6] + key2[6] * 17 + (mac[5] ^ data[i]);
		mac[6] = key2[2] * data[i] + key2[3] * mac[5] + key2[5] * 19 + (mac[6] ^ data[i]);
		mac[7] = key2[3] * data[i] + key2[0] * mac[4] + key2[4] * 23 + (mac[7] ^ data[i]);
	}
}

void IntegrityCalc::finalaize(uint8_t* clcIntegrity) {
	memcpy(clcIntegrity, mac, 8);
}
