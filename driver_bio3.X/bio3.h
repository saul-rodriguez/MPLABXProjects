/* 
 * File:   bio3.h
 * Author: saul
 *
 * Created on September 15, 2016, 3:53 PM
 * 
 * Pin assignment:
 * 
 * 
 * RA5 -> RESETN
 * RC2 -> DATA
 * RC3 -> CLK
 
 * 
 */

#ifndef BIO3_H
#define	BIO3_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"

//Implantable structure    
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

//Vinnova structure
typedef struct VIN_bits_stuct {
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
    
    unsigned CapSel0    :1;
    unsigned CapSel1    :1;
    unsigned CapSel2    :1;
    unsigned CapSel3    :1;
    unsigned CcompSel0  :1;
    unsigned CcompSel1  :1;
    unsigned EnRdegHF0  :1;    
    unsigned EnRdegHF1  :1;
    
    unsigned EnRdeg     :1;
    unsigned DP0        :1;
    unsigned DP1        :1;
    unsigned DP2        :1;
    unsigned DN0        :1;
    unsigned DN1        :1;
    unsigned EnHF       :1;
    unsigned EnMF       :1;
    
    unsigned EnLF       :1;    
} VIN_bits;

typedef union {
    unsigned short data[3];
    VIN_bits data_bits;
} VIN;

#define VIN_LENGTH 33




void BIO_config(BIO3 conf);
void VIN_config(VIN conf);

#ifdef	__cplusplus
}
#endif

#endif	/* BIO3_H */

