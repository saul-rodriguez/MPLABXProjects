/* 
 * File:   comm.h
 * Author: saul
 *
 * Created on January 24, 2017, 10:11 AM
 */

#ifndef COMM_H
#define	COMM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "bio3.h"
    
//uncomment if inductive coupling is used for power and communications
//#define INDUCTIVE_POW

    
#define BUFF_SIZE 10
extern volatile unsigned char mess_rec[BUFF_SIZE];   //Buffer to store USART RX data
extern volatile unsigned char mess_rec_size;

#define MEAS_MAX 370
#define MEAS_MIN  86

void mess_handler(); //Process data received from the USART
void config_ASIC();
void read_ADC_channels();
void measure_Impedance();
void measure_Impedance_no_offset();
void measure_Offset();
void measure_Impedance_SE();
unsigned char calculate_checksum(unsigned char* data, unsigned char num);
void calibrate_reader();
void sweep();

//#ifdef BIOASIC
//unsigned char measure(short* I, short* Q, BIO3 asic);
//#else
unsigned char measure(short* I, short* Q, VIN asic);
//#endif

#ifdef	__cplusplus
}
#endif

#endif	/* COMM_H */

