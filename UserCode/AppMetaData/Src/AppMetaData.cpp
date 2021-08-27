/*
 * AppMetaData.cpp
 *
 *  Created on: Aug 14, 2021
 *      Author: Javad Ramezanzadeh
 */

#include <IntegrityCalc.h>
#include "AppMetaData.h"
#include "Debug.h"

AppMetaData::AppMetaData() {
	// TODO Auto-generated constructor stub
	mMagic = 0;
	memset(mRevision, 0, 8);
	mAppSize = 0;
	memset(mAppIntegrityChk, 0, 8);
	memset(mMac, 0, 8);

}

AppMetaData::~AppMetaData() {
	// TODO Auto-generated destructor stub
}

AppMetaData::AppMetaData(uint8_t* buff) {
	uint8_t* macPtr = fromArray(buff);
	setMac(macPtr);
}

void AppMetaData::updateIntegrity() {
	calcMac(mMac);
}

int AppMetaData::toArray(uint8_t* buff, bool includeMac) {
	int idx = 0;
	memcpy(buff+idx, &mMagic, 4); idx += 4;
	memcpy(buff+idx, mRevision, 8); idx += 8;
	memcpy(buff+idx, &mAppSize, 4); idx += 4;
	memcpy(buff+idx, mAppIntegrityChk, 8); idx += 8;
	if(includeMac){
		memcpy(buff+idx, mMac, 8); idx += 8;
	}
	return idx;
}

bool AppMetaData::isValid() {
	uint8_t mac[8];

	if(mMagic != METADATA_MAGIC)
		return false;
	calcMac(mac);
	if (memcmp(mMac, mac, 8) != 0)
		return false;
	return true;

}

int AppMetaData::getByteCount()const{
	return (sizeof(mMagic) + 			/*mMagic*/
			sizeof(mRevision) + 		/*mRevision*/
			sizeof(mAppSize) + 			/*mAppSize*/
			sizeof(mAppIntegrityChk)  	/*mAppIntegrityChk*/);
}

uint8_t* AppMetaData::fromArray(uint8_t* buff) {
	setMagic(*((uint32_t*)buff)); buff += 4;
	setRevision((char*)buff); buff += 8;
	setAppSize(*((uint32_t*)buff)); buff += 4;
	setAppIntegrityChk(buff); buff += 8;
	return buff;
}

void AppMetaData::print() {
	debuger << "<<<<<<<< MetaData >>>>>>>>>" << endl;
	debuger.log(   "magic   : %08X\r\n", mMagic);
	debuger.logHex("version : ", (uint8_t*)mRevision, 8);
	debuger.log(   "app size: %d\r\n", mAppSize);
	debuger.logHex("app sign: ", mAppIntegrityChk, 8);
	debuger.logHex("mac     : ", mMac, 8);
	debuger << ">>>>>>>>>>>>><<<<<<<<<<<<<" << endl;
}

void AppMetaData::calcMac(uint8_t* mac) {
	uint8_t buff[100];
	IntegrityCalc integrityCalc;
	int len = toArray(buff);
	integrityCalc.reset();
	integrityCalc.update((char*)buff, len);
	integrityCalc.finalaize(mac);
}
