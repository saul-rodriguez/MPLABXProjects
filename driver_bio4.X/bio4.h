/*
 * File:   bio4.h
 * Author: saul
 *
 * Created on Feb 17, 2019
 * 
 * Pin assignment:
 * 
 * 
 * RA5 -> RESETN
 * RC2 -> DAT
 * RC3 -> CLK
 
 * 
 */

#ifndef BIO4_H
#define	BIO4_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
    
//uncomment if inductive coupling is used for power and communications
//#define INDUCTIVE_POW
    
//Here uncomment one of the ASICs to use
#define BIOASIC
//#define VINASIC  
    
// linear range for 10 bits ADC
//#define MEAS_MAX 370
//#define MEAS_MIN  86

//linear range for 12 bit ADC
#define MEAS_MAX 1500
//#define MEAS_MIN  344
#define MEAS_MIN  500

//Demodulator transient delay after a valid configuration
//vinnova 
#ifdef VINASIC
#define CONF_DELAY 15
#endif
    
//Tested with bio
#ifdef BIOASIC    
#define CONF_DELAY 20
#endif

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
    unsigned short datashort;
    unsigned char data[2];
    BIO3_bits data_bits;
} BIO3;

#define BIO3_LENGTH 16



typedef struct RADIO_gain_bits_struct {
    unsigned GD0     :1;
    unsigned GD1     :1;
    unsigned GD2     :1;
    unsigned GS0     :1;
    unsigned GS1     :1;
    unsigned GS2     :1;
    unsigned GS3     :1;
    unsigned NOTUSED :1;

} RADIO_gain_bits;

typedef union {
    unsigned char data;
    RADIO_gain_bits data_bits;
} RADIO_gain;



#ifdef BIOASIC
//Radio gain bit states (GAIN0 is lowest gain, GAIN7 is highest gain) Demodulator gain first!
#define GAIN0 0b00000100
#define GAIN1 0b00000101
#define GAIN2 0b00000111
#define GAIN3 0b00000011
#define GAIN4 0b00100011
#define GAIN5 0b01100011
#define GAIN6 0b01101011
#define GAIN7 0b01111011
#else
//Radio gain bit states (GAIN0 is lowest gain, GAIN7 is highest gain) Generator gain first!
#define GAIN0 0b00000100
#define GAIN1 0b00100100
#define GAIN2 0b01100100
#define GAIN3 0b01101100
#define GAIN4 0b01111100
#define GAIN5 0b01111101
#define GAIN6 0b01111111
#define GAIN7 0b01111011

#endif


const unsigned char gains[8] = {
    GAIN0,
    GAIN1,
    GAIN2,
    GAIN3,
    GAIN4,
    GAIN5,
    GAIN6,
    GAIN7
};

typedef struct RADIO_freq_bits_struct {
    unsigned F0     :1;
    unsigned F1     :1;  
    unsigned F2     :1;
    unsigned F3     :1;
} RADIO_freq_bits;

typedef union {
    unsigned char data;
    RADIO_freq_bits data_bits;
} RADIO_freq;

//Radio frequency bit states (FREQ0 = 1 MHz, FREQ10 = 1 kHZ))
#define FREQ0  0b00000000
#define FREQ1  0b00000001
#define FREQ2  0b00000010
#define FREQ3  0b00000011
#define FREQ4  0b00000100
#define FREQ5  0b00000101
#define FREQ6  0b00000110
#define FREQ7  0b00000111
#define FREQ8  0b00001000
#define FREQ9  0b00001001
#define FREQ10 0b00001010

const unsigned char freqs[11] = {
    FREQ0,
    FREQ1,
    FREQ2,
    FREQ3,
    FREQ4,
    FREQ5,
    FREQ6,
    FREQ7,
    FREQ8,
    FREQ9,
    FREQ10    
};

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
    unsigned short datas[3];
    unsigned char data[5];
    VIN_bits data_bits;
} VIN;

#define VIN_LENGTH 33

#define FILT_FREQ0  0b00100000011000111
#define FILT_FREQ1  0b00100000011001111
#define FILT_FREQ2  0b00100000001101111
#define FILT_FREQ3  0b00100000000111111
#define FILT_FREQ4  0b01000100100001111
#define FILT_FREQ5  0b01000100000001111
#define FILT_FREQ6  0b01010010000001111
//#define FILT_FREQ7  0b01011001000001111
#define FILT_FREQ7  0b10000100100001111
#define FILT_FREQ8  0b10000100000001111
#define FILT_FREQ9  0b10010010000001111
#define FILT_FREQ10 0b10011001000001111

typedef struct VINfilt_bits_struct {
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
} VINfilt_bits;

typedef union {
    unsigned long datal;
    unsigned char data[3];
    VINfilt_bits data_bits;
} VINfilt;

const unsigned long filt[11] = {
    FILT_FREQ0,
    FILT_FREQ1,
    FILT_FREQ2,
    FILT_FREQ3,
    FILT_FREQ4,
    FILT_FREQ5,
    FILT_FREQ6,
    FILT_FREQ7,
    FILT_FREQ8,
    FILT_FREQ9,
    FILT_FREQ10    
};


//void BIO_config(BIO3 conf);
//void VIN_config(VIN conf);



//Common VIN and BIO
void BIO_sweep(void);
void BIO_turnOffADC(void);
void BIO_messageHandler(void);

#ifdef BIOASIC
void BIO_config(BIO3 conf);
void BIO_setGain(BIO3* asic, unsigned char gain_index);
void BIO_setFreq(BIO3* asic, unsigned char freq_index);

unsigned char BIO_measure(short* I, short* Q, BIO3 asic);
unsigned char BIO_calculate_checksum(unsigned char* data, unsigned char num);
void BIO_calibrate_reader(void);
void BIO_changeTxPolarity(void);

#else
//TODO: All these names should be changed to BIO_ 
void config(VIN conf);
void setGain(VIN* asic, unsigned char gain_index);
void setFreq(VIN* asic, unsigned char freq_index);
void setFilt(VIN* asic, unsigned char freq_index);
unsigned char BIO_measure(short* I, short* Q, VIN asic);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* BIO4_H */

