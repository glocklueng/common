#include "NVM.h"
#include "eeprom.h"

//TODO: implement VirtAddVarTab

extern uint16_t VirtAddVarTab[NB_OF_VAR];

int NVM_Init(void){
	HAL_FLASH_Unlock();
	return EE_Init(); //Initialize pages
}

//Write array of variables one by one
int NVM_Store_Variables(uint16_t location, int size, uint16_t* data){
	if((size+location) >= NB_OF_VAR){ //Not enough memory locations to store all data
		return -1;
	}
	int status = 0;
	for(int i = size-1; i >= 0; i--){
		status = EE_WriteVariable(VirtAddVarTab[location+i], data[i]);
		if(status != 0){
			return status;
		}
	}

	return 0;
}

//Read array of variables one by one
int NVM_Retrieve_Variables(uint16_t location, int size, uint16_t* data){
	if((size+location) >= NB_OF_VAR){ //Not enough memory locations to retrieve all data
		return -1;
	}
	int readStatus = 0;
	int status = 0;
	for(int i = 0; i < size; i++){
		status = EE_ReadVariable(VirtAddVarTab[location+i], &(data[i]));
		if(status == NO_VALID_PAGE){
			return status;
		}else if(status == 1){
			readStatus = 1;
		}
	}
	
	/* Return readStatus value: (0: variable exist, 1: variable doesn't exist) */
	return readStatus;
}