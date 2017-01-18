/*
 * can_comm.h
 *
 *  Created on: Apr 19, 2015
 *      Author: KabooHahahein
 */

#ifndef CAN_COMM_H_
#define CAN_COMM_H_

#define CAN_MAX_BYTE_LEN        8

typedef struct
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t ShiftUp:1;
			uint8_t ShiftDown:1;
			uint8_t ShiftClutch:1;
			uint8_t ShiftClutchRelease:1;
			uint8_t ElectricStart:1;
			uint8_t HiVStart:1; // energize
			uint8_t ICStart:1;
			uint8_t ICStartRelease:1;
		};
	} status;
} DCUCanData;

typedef struct __packed
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t MotorControllerOn:1;
			uint8_t MotorControllerOff:1;
			uint8_t IsRPM:1;
			uint8_t _bit3:1;
			uint8_t _bit4:1;
			uint8_t _bit5:1;
			uint8_t _bit6:1;
			uint8_t _bit7:1;
		};
	} status;
	float rpm;
} VCUCanData;

/**
 *
 * BMS Packet Defines
 *
 */

typedef enum
{
	PBMS_DATA_NONE = 0,
	PBMS_DATA_MEAN_VOLTAGE = 1,
	PBMS_DATA_MAX_VOLTAGE = 2,
	PBMS_DATA_MIN_VOLTAGE = 3,
	PBMS_DATA_MEAN_TEMP = 4,
	PBMS_DATA_MAX_TEMP = 5,
	PBMS_DATA_MIN_TEMP = 6,
	PBMS_BATT_BITMASK = 7
} BMSDataType;

typedef enum
{
	PBMS_ERR_NONE = 0,
	PBMS_ERR_VoV = 1,
	PBMS_WARN_VuV = 2,
	PBMS_ERR_VuV = 3,
	PBMS_WARN_OTEMP = 4,
	PBMS_ERR_OTEMP = 5,
	PBMS_ERR_UTEMP = 6,
	PBMS_AMS_READ_ERROR = 7,
	PBMS_ERR_CELL_DELTA = 8
} BMSError;

typedef union
{
	uint8_t _bytes[6];
	struct __packed
	{
		union
		{
			uint16_t _short;
			struct
			{
				uint8_t Fault:1;
				uint8_t HiVEnabled:1;
				BMSError ErrorType:4;
				BMSDataType ExtraData:3;
			};
		} header;
		union
		{
			uint32_t errorMask; // a mask of the batteries that are vov or vuv or over temp.
			float value;
		} data;
	};
} BMSCanData;

#endif /* CAN_COMM_H_ */
