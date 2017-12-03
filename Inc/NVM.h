#ifndef __NVM_H
#define __NVM_H

#include "eeprom.h"

int NVM_Init(void);
int NVM_Store_Variables(uint16_t location, int size, uint16_t* data);
int NVM_Retrieve_Variables(uint16_t location, int size, uint16_t** data);

#endif /* __NVM_H */