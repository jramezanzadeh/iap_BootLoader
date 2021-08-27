/*
 * AppMetaData.h
 *
 *  Created on: Aug 14, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef APPMETADATA_APPMETADATA_H_
#define APPMETADATA_APPMETADATA_H_

#include "stdint.h"
#include "string.h"


#define METADATA_MAGIC          0x0BADF00D

class AppMetaData {
public:
	AppMetaData();
	AppMetaData(uint8_t * buff);
	virtual ~AppMetaData();

	void updateIntegrity();
	int toArray(uint8_t * buff, bool includeMac = false);
	uint8_t* fromArray(uint8_t * buff);
	bool isValid();
	void print();


	const uint8_t* getAppIntegrityChk() const {
		return mAppIntegrityChk;
	}

	void setAppIntegrityChk(uint8_t * integrity){
		memcpy(mAppIntegrityChk, integrity, 8);
	}

	uint32_t getMagic() const {
		return mMagic;
	}

	void setMagic(uint32_t magic) {
		this->mMagic = magic;
	}

	const char* getRevision() const {
		return mRevision;
	}

	void setRevision(char* revision){
		memcpy(mRevision, revision, 8);
	}

	uint32_t getAppSize() const {
		return mAppSize;
	}

	void setAppSize(uint32_t size) {
		this->mAppSize = size;
	}

	int getByteCount() const;

private:
	uint32_t 	mMagic;
	char 		mRevision[8];
	uint32_t 	mAppSize;
	uint8_t 	mAppIntegrityChk[8];
	uint8_t		mMac[8];

	void calcMac(uint8_t *mac);
	void setMac(uint8_t* mac){
		memcpy(mMac, mac, 8);
	}
};

#endif /* APPMETADATA_APPMETADATA_H_ */
