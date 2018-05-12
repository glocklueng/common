//DBC version:
int DBCVersion = 1;
char gitCommit[] = "8aee7d0";
//PDU can headder
#import "CRC_CALC.c"
//Message Filtring
#define CAN_NODE_ADDRESS 3

__weak int sendCanMessage(int id,int length,char *data[]);
// Incoming variables
// Outgoing variables
volatile int voltageBatteryLV;	// offset: 0 scaler: 1
volatile int statusPowerBMU;	// offset: 0 scaler: 1
volatile int statusPowerCoolingFanBattery;	// offset: 0 scaler: 1
volatile int statusPowerCoolingFanLeft;	// offset: 0 scaler: 1
volatile int statusPowerCoolingFanRight;	// offset: 0 scaler: 1
volatile int statusPowerCoolingPumpBattery;	// offset: 0 scaler: 1
volatile int statusPowerCoolingPumpLeft;	// offset: 0 scaler: 1
volatile int statusPowerCoolingPumpRight;	// offset: 0 scaler: 1
volatile int statusPowerDAU;	// offset: 0 scaler: 1
volatile int statusPowerDCU;	// offset: 0 scaler: 1
volatile int statusPowerIMD;	// offset: 0 scaler: 1
volatile int statusPowerMCLeft;	// offset: 0 scaler: 1
volatile int statusPowerMCRight;	// offset: 0 scaler: 1
volatile int statusPowerVCU;	// offset: 0 scaler: 1
volatile int stateBatteryChargeLV;	// offset: 0 scaler: 0.1
volatile int stateBatteryHealthLV;	// offset: 0 scaler: 0.1
volatile int stateBatteryPowerLV;	// offset: 0 scaler: 0.1
volatile int voltageBatteryLV;	// offset: 0 scaler: 1
volatile int voltageBusLV;	// offset: 0 scaler: 1
volatile int currentOutputDCDC;	// offset: 0 scaler: 0.01220703125
volatile int Status_DCDC;	// offset: 0 scaler: 1

// PRO_CAN 

int init_can_driver(){
	generate_CRC_lookup_table();
}

struct PDU_VERSION{
	int DBC : 8;
	char git0 : 8;
	char git1 : 8;
	char git2 : 8;
	char git3 : 8;
	char git4 : 8;
	char git5 : 8;
	char git6 : 8;
};

struct PDU_StateBatteryLV{
	unsigned int voltageBatteryLV : 14;
	unsigned int FILLER_END : 2;
};

struct PDU_ChannelStatus{
	         int statusPowerBMU : 4;
	         int statusPowerCoolingFanBattery : 4;
	         int statusPowerCoolingFanLeft : 4;
	         int statusPowerCoolingFanRight : 4;
	         int statusPowerCoolingPumpBattery : 4;
	         int statusPowerCoolingPumpLeft : 4;
	         int statusPowerCoolingPumpRight : 4;
	         int statusPowerDAU : 4;
	         int statusPowerDCU : 4;
	         int statusPowerIMD : 4;
	         int statusPowerMCLeft : 4;
	         int statusPowerMCRight : 4;
	         int statusPowerVCU : 4;
	unsigned int FILLER_END : 4;
};

struct PDU_batteryStatusLV{
	unsigned int stateBatteryChargeLV : 10;
	unsigned int stateBatteryHealthLV : 10;
	unsigned int stateBatteryPowerLV : 10;
	unsigned int voltageBatteryLV : 14;
	unsigned int voltageBusLV : 14;
	unsigned int FILLER_END : 6;
};

struct PDU_DCDC_Status{
	unsigned int currentOutputDCDC : 12;
	         int Status_DCDC : 4;
};


int parseOutCanPacket(int id, void * data) {
	switch(id) {
	}
	return(0);
}
int sendCAN_PDU_VERSION(){
	struct PDU_VERSION new_PDU_VERSION;
	new_PDU_VERSION.DBC = DBCVersion;
	new_PDU_VERSION.git0 = gitCommit[0];
	new_PDU_VERSION.git1 = gitCommit[1];
	new_PDU_VERSION.git2 = gitCommit[2];
	new_PDU_VERSION.git3 = gitCommit[3];
	new_PDU_VERSION.git4 = gitCommit[4];
	new_PDU_VERSION.git5 = gitCommit[5];
	new_PDU_VERSION.git6 = gitCommit[6];
	return sendCanMessage(30,8, &new_PDU_VERSION);
}
int sendCAN_PDU_StateBatteryLV(){
	struct PDU_StateBatteryLV new_PDU_StateBatteryLV;
	new_PDU_StateBatteryLV.voltageBatteryLV = voltageBatteryLV;
	voltageBatteryLV_fresh = 0;
	return sendCanMessage(8,2, &new_PDU_StateBatteryLV);
}
int sendCAN_PDU_ChannelStatus(){
	struct PDU_ChannelStatus new_PDU_ChannelStatus;
	new_PDU_ChannelStatus.statusPowerBMU = statusPowerBMU;
	statusPowerBMU_fresh = 0;
	new_PDU_ChannelStatus.statusPowerCoolingFanBattery = statusPowerCoolingFanBattery;
	statusPowerCoolingFanBattery_fresh = 0;
	new_PDU_ChannelStatus.statusPowerCoolingFanLeft = statusPowerCoolingFanLeft;
	statusPowerCoolingFanLeft_fresh = 0;
	new_PDU_ChannelStatus.statusPowerCoolingFanRight = statusPowerCoolingFanRight;
	statusPowerCoolingFanRight_fresh = 0;
	new_PDU_ChannelStatus.statusPowerCoolingPumpBattery = statusPowerCoolingPumpBattery;
	statusPowerCoolingPumpBattery_fresh = 0;
	new_PDU_ChannelStatus.statusPowerCoolingPumpLeft = statusPowerCoolingPumpLeft;
	statusPowerCoolingPumpLeft_fresh = 0;
	new_PDU_ChannelStatus.statusPowerCoolingPumpRight = statusPowerCoolingPumpRight;
	statusPowerCoolingPumpRight_fresh = 0;
	new_PDU_ChannelStatus.statusPowerDAU = statusPowerDAU;
	statusPowerDAU_fresh = 0;
	new_PDU_ChannelStatus.statusPowerDCU = statusPowerDCU;
	statusPowerDCU_fresh = 0;
	new_PDU_ChannelStatus.statusPowerIMD = statusPowerIMD;
	statusPowerIMD_fresh = 0;
	new_PDU_ChannelStatus.statusPowerMCLeft = statusPowerMCLeft;
	statusPowerMCLeft_fresh = 0;
	new_PDU_ChannelStatus.statusPowerMCRight = statusPowerMCRight;
	statusPowerMCRight_fresh = 0;
	new_PDU_ChannelStatus.statusPowerVCU = statusPowerVCU;
	statusPowerVCU_fresh = 0;
	return sendCanMessage(6,7, &new_PDU_ChannelStatus);
}
int sendCAN_PDU_batteryStatusLV(){
	struct PDU_batteryStatusLV new_PDU_batteryStatusLV;
	new_PDU_batteryStatusLV.stateBatteryChargeLV = stateBatteryChargeLV;
	stateBatteryChargeLV_fresh = 0;
	new_PDU_batteryStatusLV.stateBatteryHealthLV = stateBatteryHealthLV;
	stateBatteryHealthLV_fresh = 0;
	new_PDU_batteryStatusLV.stateBatteryPowerLV = stateBatteryPowerLV;
	stateBatteryPowerLV_fresh = 0;
	new_PDU_batteryStatusLV.voltageBatteryLV = voltageBatteryLV;
	voltageBatteryLV_fresh = 0;
	new_PDU_batteryStatusLV.voltageBusLV = voltageBusLV;
	voltageBusLV_fresh = 0;
	return sendCanMessage(5,8, &new_PDU_batteryStatusLV);
}
int sendCAN_PDU_DCDC_Status(){
	struct PDU_DCDC_Status new_PDU_DCDC_Status;
	new_PDU_DCDC_Status.currentOutputDCDC = currentOutputDCDC;
	currentOutputDCDC_fresh = 0;
	new_PDU_DCDC_Status.Status_DCDC = Status_DCDC;
	Status_DCDC_fresh = 0;
	return sendCanMessage(2,2, &new_PDU_DCDC_Status);
}
