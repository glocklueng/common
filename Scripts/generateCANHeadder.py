#!/usr/bin/env python

import cantools #$ pip install cantools
import os
from pprint import pprint
import subprocess
import sys
import errno

def create_dir(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise

def fWrite(string, fileHandle):
    fileHandle.write(string + '\n')

nodeName = sys.argv[1]

commonDir = 'common'
genDir = os.path.join(commonDir, 'Gen')

genIncDir = os.path.join(genDir, 'Inc')
create_dir(genIncDir) # Create genIncDir if it doesn't already exist

ScriptsDir = os.path.join(commonDir, 'Scripts')

depFile = os.path.join(genDir, 'canGen.d')

dataDir = os.path.join(commonDir, 'data')
dbFile = os.path.join(dataDir, '2018CAR.dbc')

headerFile = os.path.join(genIncDir, nodeName + '_can.h')
sourceFile = os.path.join(genIncDir, nodeName + '_can.c')

db = cantools.db.load_file(dbFile)

label = '0df2a9a'
gitClean = '0';

try:
	if call(["git", "branch"], stderr=STDOUT, stdout=open(os.devnull, 'w')) != 0:
		label = subprocess.check_output(["git", "describe" ,"--tags", "--always"]).strip()
except Exception:
	pass

gitCommit = label

def fWrite(string, fileHandle):
    fileHandle.write(string + '\n')

def generateDepedencyFile(headerFile, target):
    with open(depFile, 'w+') as depFileHandle:
        fWrite('{headerFile}: {dir}/generateCANHeadder.py {dbFile}'.format(headerFile=headerFile, dbFile=dbFile, dir=ScriptsDir), depFileHandle)
        fWrite('	{dir}/generateCANHeadder.py {target}'.format(target=target, dir=ScriptsDir), depFileHandle)


headerFileHandle = open(headerFile, "w+")
sourceFileHandle = open(sourceFile, "w+")

#make .h file

fWrite("#ifndef __"+nodeName+"_can_H\n#define __"+nodeName+"_can_H\n", headerFileHandle);
fWrite("#include \"can.h\"", headerFileHandle);

fWrite('//Message Filtering', headerFileHandle);
nodeAddress = 0
messageGroups = list()

for node in db.nodes:
	if node.name == nodeName:
		nodeAddress = node.comment.split("_")[0]
		fWrite('#define CAN_NODE_ADDRESS ' + nodeAddress, headerFileHandle);
		for messageGroup in node.comment.split("_")[1].split(","):
			if messageGroup != "":
				fWrite('#define CAN_NODE_MESSAGE_GROUP_'+messageGroup, headerFileHandle);
				messageGroups.append(messageGroup)
fWrite('', headerFileHandle);


fWrite("#endif /*__"+nodeName+"_can_H */", headerFileHandle);


fWrite('//DBC version:', sourceFileHandle)
fWrite('int DBCVersion = '+db.version+';', sourceFileHandle)
fWrite('char gitCommit[] = \"'+gitCommit+'\";', sourceFileHandle)

fWrite('//'+nodeName+' can headder', sourceFileHandle)
fWrite("#include \""+nodeName+"_can.h\"", sourceFileHandle)
fWrite('#include \"CRC_CALC.h\"', sourceFileHandle)

nodeList = list()




variables = list()
messages = list()
variablesPROCAN = list()

for mes in db.messages:
	messageUseful = 0
	for signal in mes.signals:
			if nodeName in signal.nodes:
				messageUseful = 1
				variables.append(signal)
	if messageUseful == 1:
		messages.append(mes)


fWrite('__weak int sendCanMessage(int id,int length,void *data);', sourceFileHandle)
fWrite('__weak int sendCanMessage(int id,int length,void *data);', headerFileHandle)
fWrite('// Incoming variables', sourceFileHandle)
for signal in variables:
	type = "int "
	if((signal.is_float)):
		type = "float "
	fWrite('volatile '+ type + signal.name + ';	// offset: ' + str(signal.offset)+ " scaler: "+ str(signal.scale), sourceFileHandle)
	fWrite('extern volatile '+ type + signal.name + ';	// offset: ' + str(signal.offset)+ " scaler: "+ str(signal.scale), headerFileHandle)
	fWrite('void '+ signal.name+'Received('+type+ 'newValue);', headerFileHandle)
	fWrite('__weak void '+ signal.name+'Received('+type+ 'newValue)\n{', sourceFileHandle)
	fWrite("	newValue = newValue * "+str(signal.scale)+";", sourceFileHandle)
	fWrite("	newValue = newValue + "+str(signal.offset)+";", sourceFileHandle)
	fWrite("	"+signal.name + " = newValue;", sourceFileHandle)
	fWrite("}\n", sourceFileHandle)

fWrite('// Outgoing variables', sourceFileHandle)
for mes in db.messages:
	if nodeName in mes.nodes:
		if mes.comment == 'PROCAN':
			variablesPROCAN.append('int '+mes.name+'_PRO_CAN_SEED = 127;');
			variablesPROCAN.append('int '+mes.name+'_PRO_CAN_COUNT = 0;');
		if mes.comment != 'VERSION':

			for signal in mes.signals:
				if signal.comment != "PROCAN":
					type = "int "
					if((signal.is_float)):
						type = "float "
					fWrite('extern volatile '+ type + signal.name + ';	// offset: ' + str(signal.offset)+ " scaler: "+ str(signal.scale), headerFileHandle)
					fWrite('volatile '+ type + signal.name + ';	// offset: ' + str(signal.offset)+ " scaler: "+ str(signal.scale), sourceFileHandle)
					fWrite(type+ signal.name+'Sending();', headerFileHandle)
					fWrite('__weak '+type+ signal.name+'Sending()\n{', sourceFileHandle)
					fWrite('	'+type+'sendValue = '+ signal.name+';', sourceFileHandle)
					fWrite("	sendValue = sendValue - "+str(signal.offset)+";", sourceFileHandle)
					fWrite("	sendValue = sendValue / "+str(signal.scale)+";", sourceFileHandle)
					fWrite("	return sendValue;", sourceFileHandle)
					fWrite("}\n", sourceFileHandle)



fWrite('', sourceFileHandle)
fWrite('// PRO_CAN ', sourceFileHandle)
for string in variablesPROCAN:
	fWrite('extern ' + string, headerFileHandle)
	fWrite(string, sourceFileHandle)
fWrite('', sourceFileHandle)

fWrite('int init_can_driver();', headerFileHandle)
fWrite('int init_can_driver(){', sourceFileHandle)
fWrite('	generate_CRC_lookup_table();', sourceFileHandle)
fWrite('	return 0;', sourceFileHandle)
fWrite('}', sourceFileHandle)
fWrite('', sourceFileHandle)

messagesREL = list()
for mes in db.messages:
	if nodeName in mes.nodes:
		messagesREL.append(mes)
for message in messagesREL:
	fWrite('struct ' + message.name + '{', headerFileHandle)
	totalSize = message.length*8;
	currentPos = 0;
	if message.comment == 'VERSION':
		fWrite('	int DBC : 8;', headerFileHandle)
		for i  in range(0,7):
			fWrite('	char git'+str(i)+' : 8;', headerFileHandle)


	else:
		for signal in message.signals:
			if signal.start != currentPos:
				fWrite('	unsigned int FILLER_'+ str(signal.start) + ' : ' + str(signal.start - currentPos) + ';', headerFileHandle)
			if signal.is_signed	:
				fWrite('	         int ' + signal.name + ' : ' + str(signal.length) + ';', headerFileHandle)
			else :
				fWrite('	unsigned int ' + signal.name + ' : ' + str(signal.length) + ';', headerFileHandle)
			currentPos = signal.start + signal.length
		if currentPos != totalSize:
			fWrite('	unsigned int FILLER_END : ' + str(totalSize - currentPos) + ';', headerFileHandle)
	fWrite('};', headerFileHandle)
	fWrite('', headerFileHandle)
fWrite('', headerFileHandle)


for message in messages:
	fWrite('struct ' + message.name + ' {', headerFileHandle)
	totalSize = message.length*8;
	currentPos = 0;
	for signal in message.signals:
		if signal.start != currentPos:
			fWrite('	unsigned int FILLER_'+ str(signal.start) + ' : ' + str(signal.start - currentPos) + ';', headerFileHandle)
		if signal.is_signed	:
			fWrite('		     int ' + signal.name + ' : ' + str(signal.length) + ';', headerFileHandle)
		else :
			fWrite('	unsigned int ' + signal.name + ' : ' + str(signal.length) + ';', headerFileHandle)
		currentPos = signal.start + signal.length
	if currentPos != totalSize:
		fWrite('	unsigned int FILLER_END : ' + str(totalSize - currentPos) + ';', headerFileHandle)
	fWrite('};', headerFileHandle)
	fWrite('', headerFileHandle)

fWrite('int parseCANData(int id, void * data);', headerFileHandle)
fWrite('int parseCANData(int id, void * data) {', sourceFileHandle)
fWrite('	switch(id) {', sourceFileHandle)
for message in messages:
	fWrite('		case '+ str(message.frame_id) + ' : // '+str(message.name), sourceFileHandle)
	# for signal in message.signals:
	fWrite('		{', sourceFileHandle)

	fWrite('			struct ' + message.name + ' *new_'+message.name +' = data;', sourceFileHandle)
	for signal in message.signals:
		if nodeName in signal.nodes:
			fWrite('			'+signal.name+ 'Recived(new_'+message.name +'->'+ signal.name+');', sourceFileHandle)

	fWrite('			break;', sourceFileHandle)
	fWrite('		}', sourceFileHandle)
fWrite('	}', sourceFileHandle)
fWrite('	return(0);', sourceFileHandle)
fWrite('}', sourceFileHandle)

messagesTransmit = list()

for mes in db.messages:
	if nodeName in mes.nodes:
		messagesTransmit.append(mes)
for message in messagesTransmit:
	fWrite("int sendCAN_" + message.name +"();", headerFileHandle)
	fWrite("int sendCAN_" + message.name +"(){", sourceFileHandle)
	fWrite('	struct ' + message.name + ' new_'+message.name +';', sourceFileHandle)
	if message.comment == 'VERSION':
		fWrite('	new_'+message.name +'.DBC = DBCVersion;', sourceFileHandle)
		for i  in range(0,7):
			fWrite('	new_'+message.name +'.git'+str(i)+' = gitCommit['+str(i)+'];', sourceFileHandle)
	else:
		for signal in message.signals:
			if signal.comment != 'PROCAN':
				fWrite('	new_'+message.name +'.'+signal.name+' = '+signal.name+'Sending();', sourceFileHandle)

		if message.comment == 'PROCAN':
			fWrite('	new_'+message.name +'.PRO_CAN_COUNT= '+message.name+'_PRO_CAN_COUNT++;', sourceFileHandle)
			fWrite('	'+message.name+'_PRO_CAN_COUNT = '+message.name+'_PRO_CAN_COUNT % 16;', sourceFileHandle)
			fWrite('	new_'+message.name +'.PRO_CAN_CRC= calculate_base_CRC((void *) &new_'+message.name+')^'+message.name+'_PRO_CAN_SEED;', sourceFileHandle)
	fWrite('	return sendCanMessage('+str(message.frame_id)+','+str(message.length)+',(uint8_t *) &new_'+message.name +');', sourceFileHandle)
 	fWrite("}", sourceFileHandle)


fWrite('void configCANFilters(CAN_HandleTypeDef* canHandle);', headerFileHandle)
fWrite('__weak void configCANFilters(CAN_HandleTypeDef* canHandle)\n{', sourceFileHandle)
fWrite('	CAN_FilterConfTypeDef  sFilterConfig;', sourceFileHandle)
fWrite('	sFilterConfig.FilterNumber = 0;', sourceFileHandle)
fWrite('	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;', sourceFileHandle)
fWrite('	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;', sourceFileHandle)
fWrite('	sFilterConfig.FilterIdHigh = 0x0000;', sourceFileHandle)
fWrite('	sFilterConfig.FilterIdLow = 0x0000 + ((CAN_NODE_ADDRESS)<<8);', sourceFileHandle)
fWrite('	sFilterConfig.FilterMaskIdHigh = 0x0000;', sourceFileHandle)
fWrite('	sFilterConfig.FilterMaskIdLow = 0xFF00;', sourceFileHandle)
fWrite('	sFilterConfig.FilterFIFOAssignment = 0;', sourceFileHandle)
fWrite('	sFilterConfig.FilterActivation = ENABLE;', sourceFileHandle)
fWrite('	sFilterConfig.BankNumber = 0;\n', sourceFileHandle)
fWrite('	if(HAL_CAN_ConfigFilter(canHandle, &sFilterConfig) != HAL_OK)', sourceFileHandle)
fWrite('	{', sourceFileHandle)
fWrite('	  Error_Handler();', sourceFileHandle)
fWrite('	}', sourceFileHandle)

fWrite('\n	sFilterConfig.FilterIdLow = 0x0000 + ('+str(0xFF)+'<<8);', sourceFileHandle)
fWrite('	sFilterConfig.FilterFIFOAssignment = 1;', sourceFileHandle)
fWrite('	sFilterConfig.BankNumber = 1;\n', sourceFileHandle)
fWrite('	if(HAL_CAN_ConfigFilter(canHandle, &sFilterConfig) != HAL_OK)', sourceFileHandle)
fWrite('	{', sourceFileHandle)
fWrite('	  Error_Handler();', sourceFileHandle)
fWrite('	}', sourceFileHandle)
i = 1
for messageGroup in messageGroups:
	i = i + 1
	fWrite('\n	sFilterConfig.FilterIdLow = 0x0000 + ('+messageGroup+'<<12);', sourceFileHandle)
	fWrite('	sFilterConfig.FilterFIFOAssignment = 2;', sourceFileHandle)
	fWrite('	sFilterConfig.BankNumber = '+str(i)+';\n', sourceFileHandle)
	fWrite('	if(HAL_CAN_ConfigFilter(canHandle, &sFilterConfig) != HAL_OK)', sourceFileHandle)
	fWrite('	{', sourceFileHandle)
	fWrite('	  Error_Handler();', sourceFileHandle)
	fWrite('	}', sourceFileHandle)

fWrite('}', sourceFileHandle)

headerFileHandle.close()
sourceFileHandle.close()

generateDepedencyFile(headerFile, nodeName)
generateDepedencyFile(sourceFile, nodeName)
