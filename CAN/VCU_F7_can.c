//DBC version:
int DBCVersion = 1;
char gitCommit[] = "0df2a9a";
//VCU_F7 can headder
#include "VCU_F7_can.h"
#import "CRC_CALC.c"
__weak int sendCanMessage(int id,int length,void *data);
// Incoming variables
volatile int StateInverterRight;	// offset: 90 scaler: 0.25
__weak void StateInverterRightRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	StateInverterRight = newValue;
}

volatile int TempInverterDeltaRight;	// offset: 90 scaler: 0.25
__weak void TempInverterDeltaRightRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempInverterDeltaRight = newValue;
}

volatile int TempInverterRight;	// offset: 90 scaler: 0.25
__weak void TempInverterRightRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempInverterRight = newValue;
}

volatile int TempMotorRight;	// offset: 90 scaler: 0.25
__weak void TempMotorRightRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempMotorRight = newValue;
}

volatile int TempMotorDeltaRight;	// offset: 90 scaler: 0.25
__weak void TempMotorDeltaRightRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempMotorDeltaRight = newValue;
}

volatile int CurrentHVBusInverterRight;	// offset: 0 scaler: 1
__weak void CurrentHVBusInverterRightRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	CurrentHVBusInverterRight = newValue;
}

volatile int VoltageHVBusInverterRight;	// offset: 0 scaler: 1
__weak void VoltageHVBusInverterRightRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	VoltageHVBusInverterRight = newValue;
}

volatile int SpeedMotorRight;	// offset: 90 scaler: 0.25
__weak void SpeedMotorRightRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	SpeedMotorRight = newValue;
}

volatile int TorqueEstimateRight;	// offset: 0 scaler: 1
__weak void TorqueEstimateRightRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	TorqueEstimateRight = newValue;
}

volatile int TorqueAvailableDriveRight;	// offset: 0 scaler: 1
__weak void TorqueAvailableDriveRightRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	TorqueAvailableDriveRight = newValue;
}

volatile int TorqueAvailableBrakingRight;	// offset: 0 scaler: 1
__weak void TorqueAvailableBrakingRightRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	TorqueAvailableBrakingRight = newValue;
}

volatile int StateInverterLeft;	// offset: 90 scaler: 0.25
__weak void StateInverterLeftRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	StateInverterLeft = newValue;
}

volatile int TempInverterDeltaLeft;	// offset: 90 scaler: 0.25
__weak void TempInverterDeltaLeftRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempInverterDeltaLeft = newValue;
}

volatile int TempInverterLeft;	// offset: 90 scaler: 0.25
__weak void TempInverterLeftRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempInverterLeft = newValue;
}

volatile int TempMotorLeft;	// offset: 90 scaler: 0.25
__weak void TempMotorLeftRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempMotorLeft = newValue;
}

volatile int TempMotorDeltaLeft;	// offset: 90 scaler: 0.25
__weak void TempMotorDeltaLeftRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	TempMotorDeltaLeft = newValue;
}

volatile int CurrentHVBusInverterLeft;	// offset: 0 scaler: 1
__weak void CurrentHVBusInverterLeftRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	CurrentHVBusInverterLeft = newValue;
}

volatile int VoltageHVBusInverterLeft;	// offset: 0 scaler: 1
__weak void VoltageHVBusInverterLeftRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	VoltageHVBusInverterLeft = newValue;
}

volatile int SpeedMotorLeft;	// offset: 90 scaler: 0.25
__weak void SpeedMotorLeftRecived(int newValue)
{
	newValue = newValue * 0.25;
	newValue = newValue + 90;
	SpeedMotorLeft = newValue;
}

volatile int TorqueEstimateLeft;	// offset: 0 scaler: 1
__weak void TorqueEstimateLeftRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	TorqueEstimateLeft = newValue;
}

volatile int TorqueAvailableDriveLeft;	// offset: 0 scaler: 1
__weak void TorqueAvailableDriveLeftRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	TorqueAvailableDriveLeft = newValue;
}

volatile int TorqueAvailableBrakingLeft;	// offset: 0 scaler: 1
__weak void TorqueAvailableBrakingLeftRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	TorqueAvailableBrakingLeft = newValue;
}

volatile int SpeedWheelRightBack;	// offset: 60 scaler: 0.000686648127167
__weak void SpeedWheelRightBackRecived(int newValue)
{
	newValue = newValue * 0.000686648127167;
	newValue = newValue + 60;
	SpeedWheelRightBack = newValue;
}

volatile int SpeedWheelLeftBack;	// offset: 60 scaler: 0.000686648127167
__weak void SpeedWheelLeftBackRecived(int newValue)
{
	newValue = newValue * 0.000686648127167;
	newValue = newValue + 60;
	SpeedWheelLeftBack = newValue;
}

volatile int voltageBatteryLV;	// offset: 0 scaler: 1
__weak void voltageBatteryLVRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	voltageBatteryLV = newValue;
}

volatile int voltageBatteryHV;	// offset: 0 scaler: 1
__weak void voltageBatteryHVRecived(int newValue)
{
	newValue = newValue * 1;
	newValue = newValue + 0;
	voltageBatteryHV = newValue;
}

volatile int currentDCBatteryHV;	// offset: 0 scaler: 0.001
__weak void currentDCBatteryHVRecived(int newValue)
{
	newValue = newValue * 0.001;
	newValue = newValue + 0;
	currentDCBatteryHV = newValue;
}

volatile int powerBatteryHV;	// offset: 0 scaler: 0.01
__weak void powerBatteryHVRecived(int newValue)
{
	newValue = newValue * 0.01;
	newValue = newValue + 0;
	powerBatteryHV = newValue;
}

volatile int voltageBusHV;	// offset: 0 scaler: 0.1
__weak void voltageBusHVRecived(int newValue)
{
	newValue = newValue * 0.1;
	newValue = newValue + 0;
	voltageBusHV = newValue;
}

volatile int SpeedWheelLeftFront;	// offset: 60 scaler: 0.000686648127167
__weak void SpeedWheelLeftFrontRecived(int newValue)
{
	newValue = newValue * 0.000686648127167;
	newValue = newValue + 60;
	SpeedWheelLeftFront = newValue;
}

volatile int SpeedWheelRightFront;	// offset: 60 scaler: 0.000686648127167
__weak void SpeedWheelRightFrontRecived(int newValue)
{
	newValue = newValue * 0.000686648127167;
	newValue = newValue + 60;
	SpeedWheelRightFront = newValue;
}

// Outgoing variables
volatile int VoltageLimitHighInverterRight;	// offset: 0 scaler: 1
__weak int VoltageLimitHighInverterRightSending()
{
	int sendValue = VoltageLimitHighInverterRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int VoltageLimitLowInverterRight;	// offset: 0 scaler: 1
__weak int VoltageLimitLowInverterRightSending()
{
	int sendValue = VoltageLimitLowInverterRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int CurrentLimitDschrgInverterRight;	// offset: 0 scaler: 1
__weak int CurrentLimitDschrgInverterRightSending()
{
	int sendValue = CurrentLimitDschrgInverterRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int CurrentLimitChargeInverterRight;	// offset: 0 scaler: 1
__weak int CurrentLimitChargeInverterRightSending()
{
	int sendValue = CurrentLimitChargeInverterRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int InverterCommandRight;	// offset: 0 scaler: 1
__weak int InverterCommandRightSending()
{
	int sendValue = InverterCommandRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int SpeedLimitForwardRight;	// offset: 0 scaler: 1
__weak int SpeedLimitForwardRightSending()
{
	int sendValue = SpeedLimitForwardRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int SpeedLimitReverseRight;	// offset: 0 scaler: 1
__weak int SpeedLimitReverseRightSending()
{
	int sendValue = SpeedLimitReverseRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int TorqueDemandRight;	// offset: 0 scaler: 1
__weak int TorqueDemandRightSending()
{
	int sendValue = TorqueDemandRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int TorqueLimitBrakingRight;	// offset: 0 scaler: 1
__weak int TorqueLimitBrakingRightSending()
{
	int sendValue = TorqueLimitBrakingRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int TorqueLimitDriveRight;	// offset: 0 scaler: 1
__weak int TorqueLimitDriveRightSending()
{
	int sendValue = TorqueLimitDriveRight;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int VoltageLimitHighInverterLeft;	// offset: 0 scaler: 1
__weak int VoltageLimitHighInverterLeftSending()
{
	int sendValue = VoltageLimitHighInverterLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int VoltageLimitLowInverterLeft;	// offset: 0 scaler: 1
__weak int VoltageLimitLowInverterLeftSending()
{
	int sendValue = VoltageLimitLowInverterLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int CurrentLimitDschrgInverterLeft;	// offset: 0 scaler: 1
__weak int CurrentLimitDschrgInverterLeftSending()
{
	int sendValue = CurrentLimitDschrgInverterLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int CurrentLimitChargeInverterLeft;	// offset: 0 scaler: 1
__weak int CurrentLimitChargeInverterLeftSending()
{
	int sendValue = CurrentLimitChargeInverterLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int InverterCommandLeft;	// offset: 0 scaler: 1
__weak int InverterCommandLeftSending()
{
	int sendValue = InverterCommandLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int SpeedLimitForwardLeft;	// offset: 0 scaler: 1
__weak int SpeedLimitForwardLeftSending()
{
	int sendValue = SpeedLimitForwardLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int SpeedLimitReverseLeft;	// offset: 0 scaler: 1
__weak int SpeedLimitReverseLeftSending()
{
	int sendValue = SpeedLimitReverseLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int TorqueDemandLeft;	// offset: 0 scaler: 1
__weak int TorqueDemandLeftSending()
{
	int sendValue = TorqueDemandLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int TorqueLimitBrakingLeft;	// offset: 0 scaler: 1
__weak int TorqueLimitBrakingLeftSending()
{
	int sendValue = TorqueLimitBrakingLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}

volatile int TorqueLimitDriveLeft;	// offset: 0 scaler: 1
__weak int TorqueLimitDriveLeftSending()
{
	int sendValue = TorqueLimitDriveLeft;
	sendValue = sendValue - 0;
	sendValue = sendValue / 1;
	return sendValue;
}


// PRO_CAN 
int VoltageLimitRight_PRO_CAN_SEED = 127;
int VoltageLimitRight_PRO_CAN_COUNT = 0;
int CurrentLimitRight_PRO_CAN_SEED = 127;
int CurrentLimitRight_PRO_CAN_COUNT = 0;
int SpeedLimitRight_PRO_CAN_SEED = 127;
int SpeedLimitRight_PRO_CAN_COUNT = 0;
int TorqueLimitRight_PRO_CAN_SEED = 127;
int TorqueLimitRight_PRO_CAN_COUNT = 0;
int VoltageLimitLeft_PRO_CAN_SEED = 127;
int VoltageLimitLeft_PRO_CAN_COUNT = 0;
int CurrentLimitLeft_PRO_CAN_SEED = 127;
int CurrentLimitLeft_PRO_CAN_COUNT = 0;
int SpeedLimitLeft_PRO_CAN_SEED = 127;
int SpeedLimitLeft_PRO_CAN_COUNT = 0;
int TorqueLimitLeft_PRO_CAN_SEED = 127;
int TorqueLimitLeft_PRO_CAN_COUNT = 0;

int init_can_driver(){
	generate_CRC_lookup_table();
}

struct VCU_VERSION{
	int DBC : 8;
	char git0 : 8;
	char git1 : 8;
	char git2 : 8;
	char git3 : 8;
	char git4 : 8;
	char git5 : 8;
	char git6 : 8;
};

struct VoltageLimitRight{
	unsigned int VoltageLimitHighInverterRight : 12;
	unsigned int VoltageLimitLowInverterRight : 12;
	unsigned int FILLER_48 : 24;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};

struct CurrentLimitRight{
	unsigned int CurrentLimitDschrgInverterRight : 12;
	unsigned int CurrentLimitChargeInverterRight : 12;
	unsigned int FILLER_48 : 24;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};

struct SpeedLimitRight{
	unsigned int InverterCommandRight : 16;
	unsigned int SpeedLimitForwardRight : 16;
	unsigned int SpeedLimitReverseRight : 16;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};

struct TorqueLimitRight{
	unsigned int TorqueDemandRight : 16;
	unsigned int TorqueLimitBrakingRight : 16;
	unsigned int TorqueLimitDriveRight : 16;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};

struct VoltageLimitLeft{
	unsigned int VoltageLimitHighInverterLeft : 12;
	unsigned int VoltageLimitLowInverterLeft : 12;
	unsigned int FILLER_48 : 24;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};

struct CurrentLimitLeft{
	unsigned int CurrentLimitDschrgInverterLeft : 12;
	unsigned int CurrentLimitChargeInverterLeft : 12;
	unsigned int FILLER_48 : 24;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};

struct SpeedLimitLeft{
	unsigned int InverterCommandLeft : 16;
	unsigned int SpeedLimitForwardLeft : 16;
	unsigned int SpeedLimitReverseLeft : 16;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};

struct TorqueLimitLeft{
	unsigned int TorqueDemandLeft : 16;
	unsigned int TorqueLimitBrakingLeft : 16;
	unsigned int TorqueLimitDriveLeft : 16;
	         int PRO_CAN_RES : 4;
	         int PRO_CAN_COUNT : 4;
	         int PRO_CAN_CRC : 8;
};


struct TempInverterRight {
		     int StateInverterRight : 12;
		     int TempInverterDeltaRight : 12;
		     int TempInverterRight : 12;
		     int InverterAUTHSEEDRight : 12;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct TempMotorRight {
		     int TempMotorRight : 12;
		     int TempMotorDeltaRight : 12;
	unsigned int FILLER_48 : 24;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct BusHVFeedbackRight {
	unsigned int CurrentHVBusInverterRight : 16;
	unsigned int VoltageHVBusInverterRight : 16;
	unsigned int FILLER_48 : 16;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct SpeedFeedbackRight {
		     int SpeedMotorRight : 16;
	unsigned int FILLER_48 : 32;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct TorqueFeedbackRight {
	unsigned int TorqueEstimateRight : 16;
	unsigned int TorqueAvailableDriveRight : 16;
	unsigned int TorqueAvailableBrakingRight : 16;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_CRC : 8;
};

struct TempInverterLeft {
		     int StateInverterLeft : 12;
		     int TempInverterDeltaLeft : 12;
		     int TempInverterLeft : 12;
		     int InverterAUTHSEEDLeft : 12;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct TempMotorLeft {
		     int TempMotorLeft : 12;
		     int TempMotorDeltaLeft : 12;
	unsigned int FILLER_48 : 24;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct BusHVFeedbackLeft {
	unsigned int CurrentHVBusInverterLeft : 16;
	unsigned int VoltageHVBusInverterLeft : 16;
	unsigned int FILLER_48 : 16;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct SpeedFeedbackLeft {
		     int SpeedMotorLeft : 16;
	unsigned int FILLER_48 : 32;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_CRC : 8;
};

struct TorqueFeedbackLeft {
	unsigned int TorqueEstimateLeft : 16;
	unsigned int TorqueAvailableDriveLeft : 16;
	unsigned int TorqueAvailableBrakingLeft : 16;
		     int PRO_CAN_COUNT : 4;
		     int PRO_CAN_RES : 4;
		     int PRO_CAN_CRC : 8;
};

struct WSBRR_WheelData {
		     int SpeedWheelRightBack : 18;
	unsigned int FILLER_END : 6;
};

struct WSBRL_WheelData {
		     int SpeedWheelLeftBack : 18;
	unsigned int FILLER_END : 6;
};

struct PDU_StateBatteryLV {
	unsigned int voltageBatteryLV : 14;
	unsigned int FILLER_END : 2;
};

struct BMU_stateBatteryHV {
	unsigned int voltageBatteryHV : 20;
		     int currentDCBatteryHV : 22;
		     int powerBatteryHV : 22;
};

struct BMU_stateBusHV {
	unsigned int voltageBusHV : 22;
	unsigned int FILLER_24 : 2;
		     int stateContactorNegative : 3;
		     int stateContactorPositive : 3;
	unsigned int FILLER_32 : 2;
	unsigned int voltageCellMax : 16;
	unsigned int voltageCellMin : 16;
};

struct WSBFL_WheelData {
		     int SpeedWheelLeftFront : 18;
	unsigned int FILLER_END : 6;
};

struct WSBFR_WheelData {
		     int SpeedWheelRightFront : 18;
	unsigned int FILLER_END : 6;
};

int parseCANData(int id, void * data) {
	switch(id) {
		case 28 : // TempInverterRight
		{
			struct TempInverterRight *new_TempInverterRight = data;
			StateInverterRightRecived(new_TempInverterRight->StateInverterRight);
			TempInverterDeltaRightRecived(new_TempInverterRight->TempInverterDeltaRight);
			TempInverterRightRecived(new_TempInverterRight->TempInverterRight);
			break;
		}
		case 27 : // TempMotorRight
		{
			struct TempMotorRight *new_TempMotorRight = data;
			TempMotorRightRecived(new_TempMotorRight->TempMotorRight);
			TempMotorDeltaRightRecived(new_TempMotorRight->TempMotorDeltaRight);
			break;
		}
		case 26 : // BusHVFeedbackRight
		{
			struct BusHVFeedbackRight *new_BusHVFeedbackRight = data;
			CurrentHVBusInverterRightRecived(new_BusHVFeedbackRight->CurrentHVBusInverterRight);
			VoltageHVBusInverterRightRecived(new_BusHVFeedbackRight->VoltageHVBusInverterRight);
			break;
		}
		case 25 : // SpeedFeedbackRight
		{
			struct SpeedFeedbackRight *new_SpeedFeedbackRight = data;
			SpeedMotorRightRecived(new_SpeedFeedbackRight->SpeedMotorRight);
			break;
		}
		case 24 : // TorqueFeedbackRight
		{
			struct TorqueFeedbackRight *new_TorqueFeedbackRight = data;
			TorqueEstimateRightRecived(new_TorqueFeedbackRight->TorqueEstimateRight);
			TorqueAvailableDriveRightRecived(new_TorqueFeedbackRight->TorqueAvailableDriveRight);
			TorqueAvailableBrakingRightRecived(new_TorqueFeedbackRight->TorqueAvailableBrakingRight);
			break;
		}
		case 19 : // TempInverterLeft
		{
			struct TempInverterLeft *new_TempInverterLeft = data;
			StateInverterLeftRecived(new_TempInverterLeft->StateInverterLeft);
			TempInverterDeltaLeftRecived(new_TempInverterLeft->TempInverterDeltaLeft);
			TempInverterLeftRecived(new_TempInverterLeft->TempInverterLeft);
			break;
		}
		case 18 : // TempMotorLeft
		{
			struct TempMotorLeft *new_TempMotorLeft = data;
			TempMotorLeftRecived(new_TempMotorLeft->TempMotorLeft);
			TempMotorDeltaLeftRecived(new_TempMotorLeft->TempMotorDeltaLeft);
			break;
		}
		case 17 : // BusHVFeedbackLeft
		{
			struct BusHVFeedbackLeft *new_BusHVFeedbackLeft = data;
			CurrentHVBusInverterLeftRecived(new_BusHVFeedbackLeft->CurrentHVBusInverterLeft);
			VoltageHVBusInverterLeftRecived(new_BusHVFeedbackLeft->VoltageHVBusInverterLeft);
			break;
		}
		case 16 : // SpeedFeedbackLeft
		{
			struct SpeedFeedbackLeft *new_SpeedFeedbackLeft = data;
			SpeedMotorLeftRecived(new_SpeedFeedbackLeft->SpeedMotorLeft);
			break;
		}
		case 15 : // TorqueFeedbackLeft
		{
			struct TorqueFeedbackLeft *new_TorqueFeedbackLeft = data;
			TorqueEstimateLeftRecived(new_TorqueFeedbackLeft->TorqueEstimateLeft);
			TorqueAvailableDriveLeftRecived(new_TorqueFeedbackLeft->TorqueAvailableDriveLeft);
			TorqueAvailableBrakingLeftRecived(new_TorqueFeedbackLeft->TorqueAvailableBrakingLeft);
			break;
		}
		case 10 : // WSBRR_WheelData
		{
			struct WSBRR_WheelData *new_WSBRR_WheelData = data;
			SpeedWheelRightBackRecived(new_WSBRR_WheelData->SpeedWheelRightBack);
			break;
		}
		case 9 : // WSBRL_WheelData
		{
			struct WSBRL_WheelData *new_WSBRL_WheelData = data;
			SpeedWheelLeftBackRecived(new_WSBRL_WheelData->SpeedWheelLeftBack);
			break;
		}
		case 8 : // PDU_StateBatteryLV
		{
			struct PDU_StateBatteryLV *new_PDU_StateBatteryLV = data;
			voltageBatteryLVRecived(new_PDU_StateBatteryLV->voltageBatteryLV);
			break;
		}
		case 7 : // BMU_stateBatteryHV
		{
			struct BMU_stateBatteryHV *new_BMU_stateBatteryHV = data;
			voltageBatteryHVRecived(new_BMU_stateBatteryHV->voltageBatteryHV);
			currentDCBatteryHVRecived(new_BMU_stateBatteryHV->currentDCBatteryHV);
			powerBatteryHVRecived(new_BMU_stateBatteryHV->powerBatteryHV);
			break;
		}
		case 3 : // BMU_stateBusHV
		{
			struct BMU_stateBusHV *new_BMU_stateBusHV = data;
			voltageBusHVRecived(new_BMU_stateBusHV->voltageBusHV);
			break;
		}
		case 1 : // WSBFL_WheelData
		{
			struct WSBFL_WheelData *new_WSBFL_WheelData = data;
			SpeedWheelLeftFrontRecived(new_WSBFL_WheelData->SpeedWheelLeftFront);
			break;
		}
		case 0 : // WSBFR_WheelData
		{
			struct WSBFR_WheelData *new_WSBFR_WheelData = data;
			SpeedWheelRightFrontRecived(new_WSBFR_WheelData->SpeedWheelRightFront);
			break;
		}
	}
	return(0);
}
int sendCAN_VCU_VERSION(){
	struct VCU_VERSION new_VCU_VERSION;
	new_VCU_VERSION.DBC = DBCVersion;
	new_VCU_VERSION.git0 = gitCommit[0];
	new_VCU_VERSION.git1 = gitCommit[1];
	new_VCU_VERSION.git2 = gitCommit[2];
	new_VCU_VERSION.git3 = gitCommit[3];
	new_VCU_VERSION.git4 = gitCommit[4];
	new_VCU_VERSION.git5 = gitCommit[5];
	new_VCU_VERSION.git6 = gitCommit[6];
	return sendCanMessage(29,8,(uint8_t *) &new_VCU_VERSION);
}
int sendCAN_VoltageLimitRight(){
	struct VoltageLimitRight new_VoltageLimitRight;
	new_VoltageLimitRight.VoltageLimitHighInverterRight = VoltageLimitHighInverterRightSending();
	new_VoltageLimitRight.VoltageLimitLowInverterRight = VoltageLimitLowInverterRightSending();
	new_VoltageLimitRight.PRO_CAN_COUNT= VoltageLimitRight_PRO_CAN_COUNT++;
	VoltageLimitRight_PRO_CAN_COUNT = VoltageLimitRight_PRO_CAN_COUNT % 16;
	new_VoltageLimitRight.PRO_CAN_CRC= calculate_base_CRC((void *) &new_VoltageLimitRight)^VoltageLimitRight_PRO_CAN_SEED;
	return sendCanMessage(23,8,(uint8_t *) &new_VoltageLimitRight);
}
int sendCAN_CurrentLimitRight(){
	struct CurrentLimitRight new_CurrentLimitRight;
	new_CurrentLimitRight.CurrentLimitDschrgInverterRight = CurrentLimitDschrgInverterRightSending();
	new_CurrentLimitRight.CurrentLimitChargeInverterRight = CurrentLimitChargeInverterRightSending();
	new_CurrentLimitRight.PRO_CAN_COUNT= CurrentLimitRight_PRO_CAN_COUNT++;
	CurrentLimitRight_PRO_CAN_COUNT = CurrentLimitRight_PRO_CAN_COUNT % 16;
	new_CurrentLimitRight.PRO_CAN_CRC= calculate_base_CRC((void *) &new_CurrentLimitRight)^CurrentLimitRight_PRO_CAN_SEED;
	return sendCanMessage(22,8,(uint8_t *) &new_CurrentLimitRight);
}
int sendCAN_SpeedLimitRight(){
	struct SpeedLimitRight new_SpeedLimitRight;
	new_SpeedLimitRight.InverterCommandRight = InverterCommandRightSending();
	new_SpeedLimitRight.SpeedLimitForwardRight = SpeedLimitForwardRightSending();
	new_SpeedLimitRight.SpeedLimitReverseRight = SpeedLimitReverseRightSending();
	new_SpeedLimitRight.PRO_CAN_COUNT= SpeedLimitRight_PRO_CAN_COUNT++;
	SpeedLimitRight_PRO_CAN_COUNT = SpeedLimitRight_PRO_CAN_COUNT % 16;
	new_SpeedLimitRight.PRO_CAN_CRC= calculate_base_CRC((void *) &new_SpeedLimitRight)^SpeedLimitRight_PRO_CAN_SEED;
	return sendCanMessage(21,8,(uint8_t *) &new_SpeedLimitRight);
}
int sendCAN_TorqueLimitRight(){
	struct TorqueLimitRight new_TorqueLimitRight;
	new_TorqueLimitRight.TorqueDemandRight = TorqueDemandRightSending();
	new_TorqueLimitRight.TorqueLimitBrakingRight = TorqueLimitBrakingRightSending();
	new_TorqueLimitRight.TorqueLimitDriveRight = TorqueLimitDriveRightSending();
	new_TorqueLimitRight.PRO_CAN_COUNT= TorqueLimitRight_PRO_CAN_COUNT++;
	TorqueLimitRight_PRO_CAN_COUNT = TorqueLimitRight_PRO_CAN_COUNT % 16;
	new_TorqueLimitRight.PRO_CAN_CRC= calculate_base_CRC((void *) &new_TorqueLimitRight)^TorqueLimitRight_PRO_CAN_SEED;
	return sendCanMessage(20,8,(uint8_t *) &new_TorqueLimitRight);
}
int sendCAN_VoltageLimitLeft(){
	struct VoltageLimitLeft new_VoltageLimitLeft;
	new_VoltageLimitLeft.VoltageLimitHighInverterLeft = VoltageLimitHighInverterLeftSending();
	new_VoltageLimitLeft.VoltageLimitLowInverterLeft = VoltageLimitLowInverterLeftSending();
	new_VoltageLimitLeft.PRO_CAN_COUNT= VoltageLimitLeft_PRO_CAN_COUNT++;
	VoltageLimitLeft_PRO_CAN_COUNT = VoltageLimitLeft_PRO_CAN_COUNT % 16;
	new_VoltageLimitLeft.PRO_CAN_CRC= calculate_base_CRC((void *) &new_VoltageLimitLeft)^VoltageLimitLeft_PRO_CAN_SEED;
	return sendCanMessage(14,8,(uint8_t *) &new_VoltageLimitLeft);
}
int sendCAN_CurrentLimitLeft(){
	struct CurrentLimitLeft new_CurrentLimitLeft;
	new_CurrentLimitLeft.CurrentLimitDschrgInverterLeft = CurrentLimitDschrgInverterLeftSending();
	new_CurrentLimitLeft.CurrentLimitChargeInverterLeft = CurrentLimitChargeInverterLeftSending();
	new_CurrentLimitLeft.PRO_CAN_COUNT= CurrentLimitLeft_PRO_CAN_COUNT++;
	CurrentLimitLeft_PRO_CAN_COUNT = CurrentLimitLeft_PRO_CAN_COUNT % 16;
	new_CurrentLimitLeft.PRO_CAN_CRC= calculate_base_CRC((void *) &new_CurrentLimitLeft)^CurrentLimitLeft_PRO_CAN_SEED;
	return sendCanMessage(13,8,(uint8_t *) &new_CurrentLimitLeft);
}
int sendCAN_SpeedLimitLeft(){
	struct SpeedLimitLeft new_SpeedLimitLeft;
	new_SpeedLimitLeft.InverterCommandLeft = InverterCommandLeftSending();
	new_SpeedLimitLeft.SpeedLimitForwardLeft = SpeedLimitForwardLeftSending();
	new_SpeedLimitLeft.SpeedLimitReverseLeft = SpeedLimitReverseLeftSending();
	new_SpeedLimitLeft.PRO_CAN_COUNT= SpeedLimitLeft_PRO_CAN_COUNT++;
	SpeedLimitLeft_PRO_CAN_COUNT = SpeedLimitLeft_PRO_CAN_COUNT % 16;
	new_SpeedLimitLeft.PRO_CAN_CRC= calculate_base_CRC((void *) &new_SpeedLimitLeft)^SpeedLimitLeft_PRO_CAN_SEED;
	return sendCanMessage(12,8,(uint8_t *) &new_SpeedLimitLeft);
}
int sendCAN_TorqueLimitLeft(){
	struct TorqueLimitLeft new_TorqueLimitLeft;
	new_TorqueLimitLeft.TorqueDemandLeft = TorqueDemandLeftSending();
	new_TorqueLimitLeft.TorqueLimitBrakingLeft = TorqueLimitBrakingLeftSending();
	new_TorqueLimitLeft.TorqueLimitDriveLeft = TorqueLimitDriveLeftSending();
	new_TorqueLimitLeft.PRO_CAN_COUNT= TorqueLimitLeft_PRO_CAN_COUNT++;
	TorqueLimitLeft_PRO_CAN_COUNT = TorqueLimitLeft_PRO_CAN_COUNT % 16;
	new_TorqueLimitLeft.PRO_CAN_CRC= calculate_base_CRC((void *) &new_TorqueLimitLeft)^TorqueLimitLeft_PRO_CAN_SEED;
	return sendCanMessage(11,8,(uint8_t *) &new_TorqueLimitLeft);
}
__weak void configCANFilters(CAN_HandleTypeDef* canHandle)
{
	CAN_FilterConfTypeDef  sFilterConfig;
	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000 + (CAN_NODE_ADDRESS)<<8;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0xFF00;
	sFilterConfig.FilterFIFOAssignment = 0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 0;

	if(HAL_CAN_ConfigFilter(&canHandle, &sFilterConfig) != HAL_OK)
	{
	  Error_Handler();
	}

	sFilterConfig.FilterIdLow = 0x0000 + (255<<8);
	sFilterConfig.FilterFIFOAssignment = 1;
	sFilterConfig.BankNumber = 1;

	if(HAL_CAN_ConfigFilter(&canHandle, &sFilterConfig) != HAL_OK)
	{
	  Error_Handler();
	}

	sFilterConfig.FilterIdLow = 0x0000 + (1<<12);
	sFilterConfig.FilterFIFOAssignment = 2;
	sFilterConfig.BankNumber = 2;

	if(HAL_CAN_ConfigFilter(&canHandle, &sFilterConfig) != HAL_OK)
	{
	  Error_Handler();
	}
}
