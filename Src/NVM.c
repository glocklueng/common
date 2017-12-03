#include "NVM.h"
#include "eeprom.h"

//TODO: implement VirtAddVarTab

int NVM_Init(void){
	return EE_Init(); //Initialize pages
}

//Write array of variables one by one
int NVM_Store_Variables(uint16_t location, int size, uint16_t* data){
	int status = 0;
	for(int i = size-1; i >= 0; i--){
		status = EE_WriteVariable(location+i, data[i]);
		if(status != 0){
			return status;
		}
	}

	return 0;
}

//Read array of variables one by one
int NVM_Retrieve_Variables(uint16_t location, int size, uint16_t** data){
	int readStatus = 0;
	int status = 0;
	for(int i = 0; i < size; i++){
		status = EE_ReadVariable(location+i, data[i]);
		if(status == NO_VALID_PAGE){
			return status;
		}else if(status == 1){
			readStatus = 1;
		}
	}
	
	/* Return readStatus value: (0: variable exist, 1: variable doesn't exist) */
	return readStatus;
}