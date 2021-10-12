/* 
 * File:   tester.h
 * Author: saul
 *
 * Created on October 12, 2021, 7:25 AM
 */

#ifndef TESTER_H
#define	TESTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "bio3.h"

//Linear range for 10 bits ADC
//#define MEAS_MAX 370
//#define MEAS_MIN  86

//Linear range for 12 bits ADC
#define MEAS_MAX 370*4
#define MEAS_MIN  86*4

    
void ADC_test();
void mess_handler();
void sweep();
unsigned char calculate_checksum(unsigned char* data, unsigned char num);

#ifdef BIOASIC
unsigned char measure(short* I, short* Q, BIO3 asic);
#else
unsigned char measure(short* I, short* Q, VIN asic);
#endif





#ifdef	__cplusplus
}
#endif

#endif	/* TESTER_H */

