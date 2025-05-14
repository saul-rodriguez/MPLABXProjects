/* 
 * File:   aska.h
 * Author: saul
 *
 * Created on September 9, 2024, 12:40 PM
 */

#ifndef ASKA_H
#define	ASKA_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include "mcc_generated_files/mcc.h"
    
#define ASKA_CONF0 0x00
#define ASKA_CONF1 0x01
#define ASKA_ELE1  0x02
#define ASKA_ELE2  0x03

#define IC_ADDRESS_0 0x00
#define IC_ADDRESS_1 0x40
#define IC_ADDRESS_2 0x80
#define IC_ADDRESS_3 0xc0

void ASKA_write_reg(uint8_t IC_addr ,uint8_t add, uint32_t value);

void ASKA_test1(uint8_t ic_add);  // 10 Hz, 0s Ramp, ON 1s, OFF 3s, PD 200  
void ASKA_test2(uint8_t ic_add);  // 10 Hz, 0.5s Ramp, ON 1s, OFF 1s, PD 200
void ASKA_test3(uint8_t ic_add);  // 50H Hz, 1s ramp, ON 1s, OFF 3s, PD 200   
void ASKA_test4(uint8_t ic_add);  // 50 Hz, 1s ramp, ON 1s, OFF 1s, PD 200
   

#ifdef	__cplusplus
}
#endif

#endif	/* ASKA_H */

