//DBC version:
int DBCVersion = 1;
char gitCommit[] = "8aee7d0";
//BMU can headder
#import "CRC_CALC.c"
//Message Filtring
#define CAN_NODE_ADDRESS 1
#define CAN_NODE_MESSAGE_GROUP_1

__weak int sendCanMessage(int id,int length,char *data[]);
// Incoming variables
volatile int CurrentHVBusInverterRight;	// offset: 0 scaler: 1
__weak void CurrentHVBusInverterRightRecived (int newValue);
volatile int VoltageHVBusInverterRight;	// offset: 0 scaler: 1
__weak void VoltageHVBusInverterRightRecived (int newValue);
volatile int CurrentHVBusInverterLeft;	// offset: 0 scaler: 1
__weak void CurrentHVBusInverterLeftRecived (int newValue);
volatile int VoltageHVBusInverterLeft;	// offset: 0 scaler: 1
__weak void VoltageHVBusInverterLeftRecived (int newValue);
volatile int currentOutputDCDC;	// offset: 0 scaler: 0.01220703125
__weak void currentOutputDCDCRecived (int newValue);
volatile int Status_DCDC;	// offset: 0 scaler: 1
__weak void Status_DCDCRecived (int newValue);
// Outgoing variables
volatile int voltageBatteryHV;	// offset: 0 scaler: 1
volatile int currentDCBatteryHV;	// offset: 0 scaler: 0.001
volatile int powerBatteryHV;	// offset: 0 scaler: 0.01
volatile int stateBatteryChargeHV;	// offset: 0 scaler: 0.1
volatile int stateBatteryHealthHV;	// offset: 0 scaler: 0.1
volatile int stateBatteryPowerHV;	// offset: 0 scaler: 0.1
volatile int TempCellMax;	// offset: 90 scaler: 0.25
volatile int TempCellMin;	// offset: 90 scaler: 0.25
volatile int stateBMS;	// offset: 0 scaler: 1
volatile int voltageBusHV;	// offset: 0 scaler: 0.1
volatile int stateContactorNegative;	// offset: 0 scaler: 1
volatile int stateContactorPositive;	// offset: 0 scaler: 1
volatile int voltageCellMax;	// offset: 0 scaler: 0.1
volatile int voltageCellMin;	// offset: 0 scaler: 0.1

// PRO_CAN 

int init_can_driver(){
	generate_CRC_lookup_table();
}

struct BMU_VERSION{
	int DBC : 8;
	char git0 : 8;
	char git1 : 8;
	char git2 : 8;
	char git3 : 8;
	char git4 : 8;
	char git5 : 8;
	char git6 : 8;
};

struct BMU_stateBatteryHV{
	unsigned int voltageBatteryHV : 20;
	         int currentDCBatteryHV : 22;
	         int powerBatteryHV : 22;
};

struct BMU_batteryStatusHV{
	unsigned int stateBatteryChargeHV : 10;
	unsigned int stateBatteryHealthHV : 10;
	unsigned int stateBatteryPowerHV : 12;
	         int TempCellMax : 10;
	         int TempCellMin : 10;
	         int stateBMS : 4;
};

struct BMU_stateBusHV{
	unsigned int voltageBusHV : 22;
	unsigned int FILLER_24 : 2;
	         int stateContactorNegative : 3;
	         int stateContactorPositive : 3;
	unsigned int FILLER_32 : 2;
	unsigned int voltageCellMax : 16;
	unsigned int voltageCellMin : 16;
};


struct BusHVFeedbackRight {
	unsigned int CurrentHVBusInverterRight : 16;
	unsigned int VoltageHVBusInverterRight : 16;
	unsigned int FILLER_48 : 16;
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

struct PDU_DCDC_Status {
	unsigned int currentOutputDCDC : 12;
		     int Status_DCDC : 4;
};

int parseOutCanPacket(int id, void * data) {
	switch(id) {
		case 26 : // BusHVFeedbackRight
		{
			struct BusHVFeedbackRight *new_BusHVFeedbackRight = data;
			CurrentHVBusInverterRight = new_BusHVFeedbackRight->CurrentHVBusInverterRight;
			CurrentHVBusInverterRightRecived(CurrentHVBusInverterRight);
			VoltageHVBusInverterRight = new_BusHVFeedbackRight->VoltageHVBusInverterRight;
			VoltageHVBusInverterRightRecived(VoltageHVBusInverterRight);
			break;
		}
		case 17 : // BusHVFeedbackLeft
		{
			struct BusHVFeedbackLeft *new_BusHVFeedbackLeft = data;
			CurrentHVBusInverterLeft = new_BusHVFeedbackLeft->CurrentHVBusInverterLeft;
			CurrentHVBusInverterLeftRecived(CurrentHVBusInverterLeft);
			VoltageHVBusInverterLeft = new_BusHVFeedbackLeft->VoltageHVBusInverterLeft;
			VoltageHVBusInverterLeftRecived(VoltageHVBusInverterLeft);
			break;
		}
		case 2 : // PDU_DCDC_Status
		{
			struct PDU_DCDC_Status *new_PDU_DCDC_Status = data;
			currentOutputDCDC = new_PDU_DCDC_Status->currentOutputDCDC;
			currentOutputDCDCRecived(currentOutputDCDC);
			Status_DCDC = new_PDU_DCDC_Status->Status_DCDC;
			Status_DCDCRecived(Status_DCDC);
			break;
		}
	}
	return(0);
}
int sendCAN_BMU_VERSION(){
	struct BMU_VERSION new_BMU_VERSION;
	new_BMU_VERSION.DBC = DBCVersion;
	new_BMU_VERSION.git0 = gitCommit[0];
	new_BMU_VERSION.git1 = gitCommit[1];
	new_BMU_VERSION.git2 = gitCommit[2];
	new_BMU_VERSION.git3 = gitCommit[3];
	new_BMU_VERSION.git4 = gitCommit[4];
	new_BMU_VERSION.git5 = gitCommit[5];
	new_BMU_VERSION.git6 = gitCommit[6];
	return sendCanMessage(32,8, &new_BMU_VERSION);
}
int sendCAN_BMU_stateBatteryHV(){
	struct BMU_stateBatteryHV new_BMU_stateBatteryHV;
	new_BMU_stateBatteryHV.voltageBatteryHV = voltageBatteryHV;
	voltageBatteryHV_fresh = 0;
	new_BMU_stateBatteryHV.currentDCBatteryHV = currentDCBatteryHV;
	currentDCBatteryHV_fresh = 0;
	new_BMU_stateBatteryHV.powerBatteryHV = powerBatteryHV;
	powerBatteryHV_fresh = 0;
	return sendCanMessage(7,8, &new_BMU_stateBatteryHV);
}
int sendCAN_BMU_batteryStatusHV(){
	struct BMU_batteryStatusHV new_BMU_batteryStatusHV;
	new_BMU_batteryStatusHV.stateBatteryChargeHV = stateBatteryChargeHV;
	stateBatteryChargeHV_fresh = 0;
	new_BMU_batteryStatusHV.stateBatteryHealthHV = stateBatteryHealthHV;
	stateBatteryHealthHV_fresh = 0;
	new_BMU_batteryStatusHV.stateBatteryPowerHV = stateBatteryPowerHV;
	stateBatteryPowerHV_fresh = 0;
	new_BMU_batteryStatusHV.TempCellMax = TempCellMax;
	TempCellMax_fresh = 0;
	new_BMU_batteryStatusHV.TempCellMin = TempCellMin;
	TempCellMin_fresh = 0;
	new_BMU_batteryStatusHV.stateBMS = stateBMS;
	stateBMS_fresh = 0;
	return sendCanMessage(4,7, &new_BMU_batteryStatusHV);
}
int sendCAN_BMU_stateBusHV(){
	struct BMU_stateBusHV new_BMU_stateBusHV;
	new_BMU_stateBusHV.voltageBusHV = voltageBusHV;
	voltageBusHV_fresh = 0;
	new_BMU_stateBusHV.stateContactorNegative = stateContactorNegative;
	stateContactorNegative_fresh = 0;
	new_BMU_stateBusHV.stateContactorPositive = stateContactorPositive;
	stateContactorPositive_fresh = 0;
	new_BMU_stateBusHV.voltageCellMax = voltageCellMax;
	voltageCellMax_fresh = 0;
	new_BMU_stateBusHV.voltageCellMin = voltageCellMin;
	voltageCellMin_fresh = 0;
	return sendCanMessage(3,8, &new_BMU_stateBusHV);
}
