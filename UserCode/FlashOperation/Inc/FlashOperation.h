/*
 * FlashOperation.h
 *
 *  Created on: Aug 14, 2021
 *      Author: Javad Ramezanzadeh
 */

#ifndef FLASHOPERATION_FLASHOPERATION_H_
#define FLASHOPERATION_FLASHOPERATION_H_

#include "AppMetaData.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"

#define flash FlashOperation::instance()
#define FLASH_PAGE_SIZE         2048

class FlashOperation {
public:
	/* Error code */
	enum
	{
		FLASHIF_OK = 0,
		FLASHIF_ERASEKO,
		FLASHIF_WRITINGCTRL_ERROR,
		FLASHIF_WRITING_ERROR
	};

	enum{
		FLASHIF_PROTECTION_NONE         = 0,
		FLASHIF_PROTECTION_PCROPENABLED = 0x1,
		FLASHIF_PROTECTION_WRPENABLED   = 0x2,
		FLASHIF_PROTECTION_RDPENABLED   = 0x4,
	};
	static FlashOperation& instance();
	virtual ~FlashOperation();
	void unlock();
	void lock();
	void erasePage(uint32_t addr);
	void writePage(uint8_t* page, uint32_t addr);
	HAL_StatusTypeDef setRDPLevel(uint32_t level);
	uint32_t getRDPLevel();
	uint8_t readOTP();
	void writeOPT(uint8_t data);
	void getAppMetaData(AppMetaData& metaData);
	void writeAppMetaData(AppMetaData& metaData);
	uint32_t getAppAddress();
	bool isValidAppExist();

private:
	FlashOperation();
	bool isStartOfSector(uint32_t addr);
	int getSector(uint32_t addr);
};

#endif /* FLASHOPERATION_FLASHOPERATION_H_ */
