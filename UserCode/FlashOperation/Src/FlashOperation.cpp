/*
 * FlashOperation.cpp
 *
 *  Created on: Aug 14, 2021
 *      Author: Javad Ramezanzadeh
 */

#include "FlashOperation.h"
#include "stm32f4xx.h"
#include "Debug.h"
#include "IntegrityCalc.h"

#define FLASH_ER_PRG_TIMEOUT	50000 /*50 s*/
/**
 * 	Sector 0  0x0800 0000 - 0x0800 3FFF 16 Kbyte
   	Sector 1  0x0800 4000 - 0x0800 7FFF 16 Kbyte
	Sector 2  0x0800 8000 - 0x0800 BFFF 16 Kbyte
	Sector 3  0x0800 C000 - 0x0800 FFFF 16 Kbyte
	Sector 4  0x0801 0000 - 0x0801 FFFF 64 Kbyte
	Sector 5  0x0802 0000 - 0x0803 FFFF 128 Kbyte
	Sector 6  0x0804 0000 - 0x0805 FFFF 128 Kbyte
	Sector 7  0x0806 0000 - 0x0807 FFFF 128 Kbyte
	Sector 8  0x0808 0000 - 0x0809 FFFF 128 Kbyte
	Sector 9  0x080A 0000 - 0x080B FFFF 128 Kbyte
	Sector 10 0x080C 0000 - 0x080D FFFF 128 Kbyte
	Sector 11 0x080E 0000 - 0x080F FFFF 128 Kbyte
	Sector 12 0x0810 0000 - 0x0811 FFFF 128 Kbyte
	Sector 13 0x0812 0000 - 0x0813 FFFF 128 Kbyte
	Sector 14 0x0814 0000 - 0x0815 FFFF 128 Kbyte
	Sector 15 0x0816 0000 - 0x0817 FFFF 128 Kbyte
 */
#define SECTOR_00_ADDR			0x08000000
#define SECTOR_01_ADDR			0x08004000
#define SECTOR_02_ADDR			0x08008000
#define SECTOR_03_ADDR			0x0800C000
#define SECTOR_04_ADDR			0x08010000
#define SECTOR_05_ADDR			0x08020000
#define SECTOR_06_ADDR			0x08040000
#define SECTOR_07_ADDR			0x08060000
#define SECTOR_08_ADDR			0x08080000
#define SECTOR_09_ADDR			0x080A0000
#define SECTOR_10_ADDR			0x080C0000
#define SECTOR_11_ADDR			0x080E0000
#define SECTOR_12_ADDR			0x08100000
#define SECTOR_13_ADDR			0x08120000
#define SECTOR_14_ADDR			0x08140000
#define SECTOR_15_ADDR			0x08160000

#define FLASH_SECTOR_TO_BE_PROTECTED (OB_WRP_SECTOR_All)

#define OTP_ADDRRESS			(FLASH_OTP_BASE + 1)
#define OTP_LOCK_ADDRRESS		(FLASH_OTP_BASE + 512)

#define METADATA_ADDRESS        SECTOR_03_ADDR
#define METADATA_SECTOR        	3
#define APPLICATION_ADDRESS     SECTOR_04_ADDR
#define APPLICATION_SECTOR 	    4

FlashOperation::FlashOperation() {
	// TODO Auto-generated constructor stub

}

FlashOperation::~FlashOperation() {
	// TODO Auto-generated destructor stub
}

bool FlashOperation::isStartOfSector(uint32_t addr) {
	if ((addr == SECTOR_00_ADDR) || (addr == SECTOR_01_ADDR)
			|| (addr == SECTOR_02_ADDR) || (addr == SECTOR_03_ADDR)
			|| (addr == SECTOR_04_ADDR) || (addr == SECTOR_05_ADDR)
			|| (addr == SECTOR_06_ADDR) || (addr == SECTOR_07_ADDR)
			|| (addr == SECTOR_08_ADDR) || (addr == SECTOR_09_ADDR)
			|| (addr == SECTOR_10_ADDR) || (addr == SECTOR_11_ADDR)
			|| (addr == SECTOR_12_ADDR) || (addr == SECTOR_13_ADDR)
			|| (addr == SECTOR_14_ADDR) || (addr == SECTOR_15_ADDR))
		return true;
	return false;
}

void FlashOperation::writeAppMetaData(AppMetaData& metaData) {
	uint8_t buff[100];

	metaData.updateIntegrity();
	metaData.print();
	int len = metaData.toArray(buff, true);
	char *p = (char*)buff;

	erasePage(METADATA_ADDRESS);
	FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

	for (int i = 0; i < len; i += 4, p += 4) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, METADATA_ADDRESS + i,
				*(uint32_t*) p);
		FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	}
}

FlashOperation& FlashOperation::instance() {
	static FlashOperation _instance;
	return _instance;
}

void FlashOperation::writePage(uint8_t* page, uint32_t addr) {

	debuger.log("Writing page[%.8X]\r\n", addr);
	erasePage(addr);
	FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	char *p = (char*)page;
	for (int i = 0; i < FLASH_PAGE_SIZE; i += 4, p += 4) {
		//		printDebug("Write i[%d]", i);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + i,
				*(uint64_t*) p);
		FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	}
	debuger.log("Wrote page[%.8x]\r\n", addr);
}

int FlashOperation::getSector(uint32_t addr) {
	if (addr < SECTOR_01_ADDR)
		return 0;
	else if (addr < SECTOR_02_ADDR)
		return 1;
	else if (addr < SECTOR_03_ADDR)
		return 2;
	else if (addr < SECTOR_04_ADDR)
		return 3;
	else if (addr < SECTOR_05_ADDR)
		return 4;
	else if (addr < SECTOR_06_ADDR)
		return 5;
	else if (addr < SECTOR_07_ADDR)
		return 6;
	else if (addr < SECTOR_08_ADDR)
		return 7;
	else if (addr < SECTOR_09_ADDR)
		return 8;
	else if (addr < SECTOR_10_ADDR)
		return 9;
	else if (addr < SECTOR_11_ADDR)
		return 10;
	else if (addr < SECTOR_12_ADDR)
		return 11;
	else if (addr < SECTOR_13_ADDR)
		return 12;
	else if (addr < SECTOR_14_ADDR)
		return 13;
	else if (addr < SECTOR_15_ADDR)
		return 14;
	return 15;
}

uint8_t FlashOperation::readOTP() {
	uint8_t *otp = (uint8_t*) OTP_ADDRRESS;
	return otp[0];
}

void FlashOperation::writeOPT(uint8_t data) {
	FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, OTP_ADDRRESS, data);
	FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, OTP_LOCK_ADDRRESS, 0x00);
	FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
	lock();
}

void FlashOperation::getAppMetaData(AppMetaData& metaData) {
	metaData = (uint8_t*) METADATA_ADDRESS;
}

void FlashOperation::unlock() {
	HAL_FLASH_Unlock();
	FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
}

void FlashOperation::lock() {
	HAL_FLASH_Lock();
	FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
}
/*
 * erase the sector if input address is start of that sector.
 * it seems that flash has been unlocked
 */
void FlashOperation::erasePage(uint32_t addr) {
	if (isStartOfSector(addr)) {
		debuger.log("erase sector[%d]\r\n", getSector(addr));
		FLASH_Erase_Sector(getSector(addr), FLASH_VOLTAGE_RANGE_3);
		debuger << "erase done" << endl;
	}
}
/*
 * set read protection level
 */
HAL_StatusTypeDef FlashOperation::setRDPLevel(uint32_t level) {
	FLASH_OBProgramInitTypeDef config;
	HAL_StatusTypeDef result = HAL_OK;
	config.OptionType = OPTIONBYTE_RDP;
	config.RDPLevel = level;

	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();

	/* Unlock the Options Bytes *************************************************/
	HAL_FLASH_OB_Unlock();

	result = HAL_FLASHEx_OBProgram(&config);

	return result;

}
/*
 * get read protection level
 */
uint32_t FlashOperation::getRDPLevel() {
	FLASH_OBProgramInitTypeDef config;
	HAL_FLASHEx_OBGetConfig(&config);
	return config.RDPLevel;
}

uint32_t FlashOperation::getAppAddress() {
	return APPLICATION_ADDRESS;
}

bool FlashOperation::isValidAppExist() {
	AppMetaData metaData;
	getAppMetaData(metaData);
	if(!metaData.isValid())
		return false;
	metaData.print();
	//calculate integrity of Application
	IntegrityCalc integrityCalc;
	uint8_t mac[8];
	char* appAddr = (char*)APPLICATION_ADDRESS;
	integrityCalc.reset();
	integrityCalc.update(appAddr, metaData.getAppSize());
	integrityCalc.finalaize(mac);
	//compare calculated integrity and saved integrity
	if(memcmp(mac, metaData.getAppIntegrityChk(), 8) != 0)
		return false;
	return true;
}

