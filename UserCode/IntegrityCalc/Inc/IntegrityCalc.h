/*
 * IntegrityCheck.h
 *
 *  Created on: Aug 14, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef INTEGRITYCHECK_INTEGRITYCHECK_H_
#define INTEGRITYCHECK_INTEGRITYCHECK_H_

#include "stdint.h"

class IntegrityCalc {
public:
	IntegrityCalc();
	virtual ~IntegrityCalc();
	void reset();
	void update(char* data, int len) ;
	void finalaize(uint8_t* clcIntegrity);

private:
	uint8_t key1[8];
	uint8_t key2[8];
	uint8_t iv[8]; // initial vector
	uint8_t mac[8];
};

#endif /* INTEGRITYCHECK_INTEGRITYCHECK_H_ */
