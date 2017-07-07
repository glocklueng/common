// (C) Waterloo Formula Electric 2017
#ifndef CAN_COMM_H_
#define CAN_COMM_H_

// For static asserts
#include "assert.h"

#define CAN_MAX_BYTE_LEN        8

// Addresses of boards, OR them together (e.g, when BMS sends to VCU, ID would be CAN_ID_BMS | CAN_ID_VCU == 0x3)
// BMS and VCU are highest priority
#define CAN_ID_BMS         (1 << 0)
#define CAN_ID_VCU         (1 << 1)
#define CAN_ID_DCU         (1 << 2)
#define CAN_ID_PDB         (1 << 3)
#define CAN_ID_DAU         (1 << 4)

// BMS to VCU packet
typedef struct __packed
{
    uint16_t stateBatteryChargeHV:10;
    uint16_t stateBatteryHealthHV:10;
    uint16_t steateBatteryPowerHV:10;
}
BMS_batteryStatusHV_CanData;

// to DCU to display voltage
typedef struct __packed
{
    uint32_t voltageBatteryHV:18;
    uint32_t currentDCBatteryHV:24;
    uint32_t powerBatteryHV:18;
}
BMS_stateBatteryHV; 

typedef struct __packed
{
    uint32_t voltageBusHV:18;
    uint8_t stateContactorNegative:3;
    uint8_t stateContactorPositive:3;
}
BMU_stateBusHV;

typedef struct __packed
{
    uint16_t maxCurrentToMCs:10;
    uint16_t bpsPressure:12;
    uint8_t bpsFailed:1;
    uint8_t hvEnable:1;
    uint8_t padding[5];
}
BMU_PowerAndBrake; // goes from BMS to VCU

typedef struct __packed
{
    uint8_t intendToCharge:1;
    uint8_t padding:7;
}
CC_IntentionToCharge; // CC to BMU

typedef struct __packed
{
    uint8_t acceptChargeRequest:1;
    uint8_t padding:7;
}
BMU_AcceptChargeRequest;


/*
typedef struct __packed
{
    uint8_t energizeStatus:1;   // Energized (1) or not energized (0)
    uint8_t bpsPressed:1;       // Brake pressed (1), or not pressed (0)
    uint8_t bpsFailed:1;        // BPS failed (1), or not failed (0)
    uint8_t reserved[7];
}
BMS_VCU_CanData;
*/
STATIC_ASSERT(sizeof(BMU_PowerAndBrake) == CAN_MAX_BYTE_LEN, BMS_VCU_CanData_sizecheck); // Make sure it's actually 3 bytes

// DCU to BMS packet
typedef struct __packed
{
    uint8_t hvToggleFromDCU:1;         // HV enabled (1), or not enabled (0)
    uint8_t hvEnableFromBMS:1;         // HV enabled (1), or not enabled (0)
    uint8_t hvPrecharging:1;
    uint8_t amsFault:1;
    uint8_t imdFault:1;
    uint8_t lowBattery:1;
    uint8_t reserved[7];
}
DCU_BMS_CanData;
STATIC_ASSERT(sizeof(DCU_BMS_CanData) == CAN_MAX_BYTE_LEN, DCU_BMS_CanData_sizecheck);

// DCU to VCU packet
typedef struct __packed
{
    uint8_t emToggleFromDCU:1;         // EM enabled (1), or not enabled (0)
    uint8_t emEnableFromVCU:1;
    uint8_t fromVCU:1;
    uint8_t reserved[7];
}
DCU_VCU_CanData;
STATIC_ASSERT(sizeof(DCU_VCU_CanData) == CAN_MAX_BYTE_LEN, DCU_VCU_CanData_sizecheck);

// DAQ to BMS packet
typedef struct __packed
{   
    uint8_t critMotorTemp:1;     // Critical motor temperature reached (1), or not reached (0)
    uint8_t reserved[7];
}
DAU_BMS_CanData;
STATIC_ASSERT(sizeof(DAU_BMS_CanData) == CAN_MAX_BYTE_LEN, DAU_BMS_CanData_sizecheck);

#endif /* CAN_COMM_H_ */
