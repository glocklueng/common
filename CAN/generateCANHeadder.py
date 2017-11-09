import cantools
from pprint import pprint
db = cantools.db.load_file('2018CAR.dbc')
import subprocess

label = '0df2a9a'

try:
	label = subprocess.check_output(["git", "describe" ,"--tags", "--always"]).strip()
except Exception:
	pass


gitCommit = label
nodeName = 'BMU'
import sys
sys.stdout = open(nodeName+"_can.c", "w")
print('//DBC version:')
print('int DBCVersion = '+db.version+';');
print('char gitCommit[] = \"'+gitCommit+'\";')

print('//'+nodeName+' can headder')
print('#import \"CRC_CALC.c\"')

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


print('__weak int sendCanMessage(int id,int length,char *data[]);')	
print('// Incoming variables')
for signal in variables:
	type = "int "
	if((signal.is_float)):
		type = "float " 
	print('volatile '+ type + signal.name + ';	// offset: ' + str(signal.offset)+ " scaler: "+ str(signal.scale))
	print('volatile int ' + signal.name + '_fresh = 0;')
print('// Outgoing variables')	
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
					print('volatile '+ type + signal.name + ';	// offset: ' + str(signal.offset)+ " scaler: "+ str(signal.scale))
					print('volatile int ' + signal.name + '_fresh = 0;')
	

print('')
print('// PRO_CAN ')
for strings in variablesPROCAN:
	print(strings)
print('')

print('int init_can_driver(){')
print('	generate_CRC_lookup_table();')
print('}')
print('')

messagesREL = list()
for mes in db.messages:
	if nodeName in mes.nodes:
		messagesREL.append(mes)
for message in messagesREL:
	print('struct ' + message.name + '{') 
	totalSize = message.length*8;
	currentPos = 0;
	if message.comment == 'VERSION':
		print('	int DBC : 8;')
		for i  in range(0,7):
			print('	char git'+str(i)+' : 8;')


	else:
		for signal in message.signals:
			if signal.start != currentPos:
				print('	unsigned int FILLER_'+ str(signal.start) + ' : ' + str(signal.start - currentPos) + ';')
			if signal.is_signed	:
				print('	         int ' + signal.name + ' : ' + str(signal.length) + ';')
			else :
				print('	unsigned int ' + signal.name + ' : ' + str(signal.length) + ';')
			currentPos = signal.start + signal.length
		if currentPos != totalSize:
			print('	unsigned int FILLER_END : ' + str(totalSize - currentPos) + ';')
	print('};') 
	print('') 
print('') 


for message in messages:
	print('struct ' + message.name + ' {') 
	totalSize = message.length*8;
	currentPos = 0;
	for signal in message.signals:
		if signal.start != currentPos:
			print('	unsigned int FILLER_'+ str(signal.start) + ' : ' + str(signal.start - currentPos) + ';')
		if signal.is_signed	:
			print('		     int ' + signal.name + ' : ' + str(signal.length) + ';')
		else :
			print('	unsigned int ' + signal.name + ' : ' + str(signal.length) + ';')
		currentPos = signal.start + signal.length
	if currentPos != totalSize:
		print('	unsigned int FILLER_END : ' + str(totalSize - currentPos) + ';')
	print('};') 
	print('') 
print('int parseOutCanPacket(int id, char *data[]) {') 
print('	switch(id) {') 
for message in messages:
	print('		case '+ str(message.frame_id) + ' : // '+str(message.name)) 
	# for signal in message.signals:
	print('		{') 
	
	print('			struct ' + message.name + ' *new_'+message.name +' = data;')
	for signal in message.signals:
		if nodeName in signal.nodes:
			print('			'+signal.name + ' = new_'+message.name +'->'+ signal.name+';')
			print('			'+signal.name+ '_fresh = 1;')

	print('			break;') 
	print('		}')
print('	}')
print('	return(0);')  
print('}') 

messagesTransmit = list()

for mes in db.messages:
	if nodeName in mes.nodes:
		messagesTransmit.append(mes) 
for message in messagesTransmit:
	print("int sendCAN_" + message.name +"(){")
	print('	struct ' + message.name + ' new_'+message.name +';')
	if message.comment == 'VERSION':
		print('	new_'+message.name +'.DBC = DBCVersion;')
		for i  in range(0,7):
			print('	new_'+message.name +'.git'+str(i)+' = gitCommit['+str(i)+'];')
	else:
		for signal in message.signals:
			if signal.comment != 'PROCAN':
				print('	new_'+message.name +'.'+signal.name+' = '+signal.name+';')
				print('	'+signal.name+ '_fresh = 0;')
		if message.comment == 'PROCAN':
			print('	new_'+message.name +'.PRO_CAN_COUNT= '+message.name+'_PRO_CAN_COUNT++;')
			print('	'+message.name+'_PRO_CAN_COUNT = '+message.name+'_PRO_CAN_COUNT % 16;')
			print('	new_'+message.name +'.PRO_CAN_CRC= calculate_base_CRC(&new_'+message.name+')^'+message.name+'_PRO_CAN_SEED;')
	print('	return sendCanMessage('+str(message.frame_id)+','+str(message.length)+', &new_'+message.name +');')
 	print("}")
