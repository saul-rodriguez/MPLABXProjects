/* 
 * File:   bio3.h
 * Author: saul
 *
 * Created on September 15, 2016, 3:53 PM
 * 
 * Pin assignment:
 * 
 * RC1 -> DATA
 * RC2 -> CLOCK
 * RC3 -> RESETN
 * 
 */

#ifndef BIO3_H
#define	BIO3_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
    
typedef struct BIO3_bits_stuct {
    unsigned RE     :1;
    unsigned FS     :1;
    unsigned GD0    :1;
    unsigned GD1    :1;
    unsigned GD2    :1;
    unsigned NS     :1;
    unsigned CE     :1;
    unsigned GS0    :1;
    unsigned GS1    :1;
    unsigned GS2    :1;
    unsigned GS3    :1;
    unsigned IQ     :1;
    unsigned F0     :1;
    unsigned F1     :1;
    unsigned F2     :1;
    unsigned F3     :1;
} BIO3_bits;

typedef union {
    unsigned short data;
    BIO3_bits data_bits;
} BIO3;
    
#define BIO3_LENGTH 16


void BIO_config(unsigned long data, unsigned char length);

#ifdef	__cplusplus
}
#endif

#endif	/* BIO3_H */

