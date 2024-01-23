/*
 * um7.h
 *
 *  Created on: Dec 20, 2016
 *      Author: gaurav
 */

#ifndef UM7_H_
#define UM7_H_

#define true 1
#define false 0
#define DREG_EULER_PHI_THETA 0x70
volatile int roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate;
int encode(int c);

enum {STATE_ZERO,STATE_S,STATE_SN,STATE_SNP,STATE_PT,STATE_DATA,STATE_CHK1,STATE_CHK0};

volatile int packet_type;
volatile int address;
volatile int packet_is_batch;
volatile int batch_length;
volatile int packet_has_data;
volatile int data[30];
volatile int data_length;
volatile int data_index;

volatile int checksum1;		// First int of checksum
volatile int checksum0;		// Second int of checksum

volatile unsigned int checksum10;			// Checksum received from packet
volatile unsigned int computed_checksum;	// Checksum computed from ints received

volatile int match_hua=0;
volatile int nahi_hua=0;

int checksum(void);
void save(void);


volatile int state =STATE_ZERO;

int encode(int c)
{
	switch(state){
	case STATE_ZERO:
		if (c == 's'){
			state = STATE_S;		// Entering state S from state Zero
		} else {
			state = STATE_ZERO;
		}
		return false;
	case STATE_S:
		if (c == 'n'){
			state = STATE_SN;		// Entering state SN from state S
		} else {
			state = STATE_ZERO;
		}
		return false;
	case STATE_SN:
		if (c == 'p'){
			state = STATE_SNP;		// Entering state SNP from state SN.  Packet header detected.
		} else {
			state = STATE_ZERO;
		}
		return false;
	case STATE_SNP:
		state = STATE_PT;			// Entering state PT from state SNP.  Decode packet type.
		packet_type = c;
		packet_has_data = (packet_type >> 7) & 0x01;
		packet_is_batch = (packet_type >> 6) & 0x01;
		batch_length    = (packet_type >> 2) & 0x0F;
		if (packet_has_data){
			if (packet_is_batch){
				data_length = 4 * batch_length;	// Each data packet is 4 bytes long
			} else {
				data_length = 4;
			}
		} else {
			data_length = 0;
		}
		return false;
	case STATE_PT:
		state = STATE_DATA;		// Next state will be READ_DATA.  Save address to memory. (eg 0x70 for a DREG_EULER_PHI_THETA packet)
		address = c;
		data_index = 0;
		return false;
	case STATE_DATA:			//  Entering state READ_DATA.  Stay in state until all data is read.
		data[data_index] = c;
		data_index++;
		if (data_index >= data_length){
			state = STATE_CHK1;	//  Data read completed.  Next state will be CHK1
		}
		return false;
	case STATE_CHK1:			// Entering state CHK1.  Next state will be CHK0
		state = STATE_CHK0;
		checksum1 = c;
		return false;
	case STATE_CHK0:
		state = STATE_ZERO;		// Entering state CHK0.  Next state will be state Zero.
		checksum0 = c;
		return checksum();
	}
}



int checksum()
{
	checksum10  = checksum1 << 8;	// Combine checksum1 and checksum0
	checksum10 |= checksum0;
	computed_checksum = 's' + 'n' + 'p' + packet_type + address;
	int i=0;
	for (i = 0; i < data_length; i++){
		computed_checksum += data[i];
	}
	if (checksum10 == computed_checksum){
		match_hua++;
		save();
		return true;
	} else {
		nahi_hua++;
		return false;
	}
}

void save()
{
	switch(address)
	{
	case DREG_EULER_PHI_THETA :		// data[6] and data[7] are unused.
		if(packet_is_batch){
			roll = data[0] << 8;
			roll |= data[1];
			pitch = data[2] << 8;
			pitch |= data[3];
			yaw = data[4] << 8;
			yaw |= data[5];
			roll_rate = data[8] << 8;
			roll_rate |= data[9];
			pitch_rate = data[10] << 8;
			pitch_rate |= data[11];
			yaw_rate = data[12] << 8;
			yaw_rate |= data[13];
		}else{
			roll = data[0] << 8;
			roll |= data[1];
			pitch = data[2] << 8;
			pitch |= data[3];
		}
		break;
	}
}




#endif /* UM7_H_ */
