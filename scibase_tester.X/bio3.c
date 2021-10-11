#include "bio3.h"

//#define WAIT __delay_ms(1)
//#define WAIT __delay_ms(2)
//#define WAIT __delay_us(2)
//#define WAIT __delay_us(5)
#define WAIT __delay_us(50)
//#define WAIT ;

/*
// RESETN in RA5
#define RESETN_L RA5 = 0;
#define RESETN_H RA5 = 1;

// CFG_CLK in RC3 
#define CLK_L out &= 0b11110111;\
                 PORTC = out;
#define CLK_H out |= 0b00001000;\
                 PORTC = out;

// CFG_DAT in RC2
#define DATA_L out &= 0b11111011;\
              PORTC = out;
#define DATA_H out |= 0b00000100;\
              PORTC = out;
*/

// RESETN in RA5
#define RESETN_L CFG_RES_SetLow()
#define RESETN_H CFG_RES_SetHigh()



// CFG_CLK in RC3 
#define CLK_L CFG_CLK_SetLow()
#define CLK_H CFG_CLK_SetHigh()

// CFG_DAT in RC2
#define DATA_L CFG_DAT_SetLow()
#define DATA_H CFG_DAT_SetHigh()




/*
 * BIO_config(data,length)
 * 
 * Sends a configuration order to the BIO3 ASIC
 * data:
 * length:
 * 
 */

/*
void BIO_config(BIO3 conf)
{
    unsigned char i, out;
    
    CLK_L;
    WAIT;
    
    RESETN_L;
    WAIT;
    
    RESETN_H;
        
    for(i = 0; i < BIO3_LENGTH; i++) {
        if (conf.datashort & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datashort >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;
        
    }    
}

void VIN_config(VIN conf)
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
*/

#ifdef BIOASIC 

void config(BIO3 conf)
{
    unsigned char i, out;
    
    CLK_L;
    WAIT;
    
    RESETN_L;
    WAIT;
    
    RESETN_H;
        
    for(i = 0; i < BIO3_LENGTH; i++) {
        if (conf.datashort & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datashort >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;
        
    }    
}


void setGain(BIO3* asic, unsigned char gain_index)
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

void setFreq(BIO3* asic, unsigned char freq_index)
{
    RADIO_freq aux;
    aux.data = freqs[freq_index];
    
    asic->data_bits.F0 = aux.data_bits.F0;
    asic->data_bits.F1 = aux.data_bits.F1;
    asic->data_bits.F2 = aux.data_bits.F2;
    asic->data_bits.F3 = aux.data_bits.F3;
        
}

#else

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

#endif
