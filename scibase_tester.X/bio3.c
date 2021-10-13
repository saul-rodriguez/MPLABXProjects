#include "bio3.h"

//#define WAIT __delay_ms(1)
//#define WAIT __delay_ms(2)
//#define WAIT __delay_us(2)
//#define WAIT __delay_us(5)
#define WAIT __delay_us(50)
//#define WAIT ;

// RESETN 
#define RESETN_L CFG_RES_SetLow()
#define RESETN_H CFG_RES_SetHigh()

// CFG_CLK 
#define CLK_L CFG_CLK_SetLow()
#define CLK_H CFG_CLK_SetHigh()

// CFG_DAT 
#define DATA_L CFG_DAT_SetLow()
#define DATA_H CFG_DAT_SetHigh()

void config(VIN conf)
{
    
      unsigned char i,j,out;
    
    CLK_L;
    WAIT;
    
    RESETN_L;
    WAIT;
    
    RESETN_H;
        
    for(i = 0; i < 16; i++) {
        if (conf.datas[0] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datas[0] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
    
    for(i = 0; i < 16; i++) {
        if (conf.datas[1] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datas[1] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
    
    for(i = 0; i < 1; i++) {
        if (conf.datas[2] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datas[2] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
   
}

void setGain(VIN* asic, unsigned char gain_index)
{
    RADIO_gain aux;
    aux.data = gains[gain_index];
    
    asic->data_bits.GD0 = aux.data_bits.GD0;
    asic->data_bits.GD1 = aux.data_bits.GD1;
    asic->data_bits.GD2 = aux.data_bits.GD2;
    asic->data_bits.GS0 = aux.data_bits.GS0;
    asic->data_bits.GS1 = aux.data_bits.GS1;
    asic->data_bits.GS2 = aux.data_bits.GS2;
    asic->data_bits.GS3 = aux.data_bits.GS3;
}

void setFreq(VIN* asic, unsigned char freq_index)
{
    RADIO_freq aux;
    aux.data = freqs[freq_index];
    
    asic->data_bits.F0 = aux.data_bits.F0;
    asic->data_bits.F1 = aux.data_bits.F1;
    asic->data_bits.F2 = aux.data_bits.F2;
    asic->data_bits.F3 = aux.data_bits.F3;
        
}

void setFilt(VIN* asic, unsigned char freq_index)
{
    VINfilt aux;
    aux.datal = filt[freq_index];
    
    asic->data[2] = aux.data[0];
    asic->data[3] = aux.data[1];
    asic->data[4] = aux.data[2];    
    
}


