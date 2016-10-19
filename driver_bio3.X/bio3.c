#include "bio3.h"

#define WAIT __delay_ms(1)



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




/*
 * BIO_config(data,length)
 * 
 * Sends a configuration order to the BIO3 ASIC
 * data:
 * length:
 * 
 */

void BIO_config(BIO3 conf)
{
    unsigned char i, out;
    
    CLK_L;
    WAIT;
    
    RESETN_L;
    WAIT;
    
    RESETN_H;
        
    for(i = 0; i < BIO3_LENGTH; i++) {
        if (conf.data & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.data >>= 1;
        
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
        if (conf.data[0] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.data[0] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
    
    for(i = 0; i < 16; i++) {
        if (conf.data[1] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.data[1] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
    
    for(i = 0; i < 1; i++) {
        if (conf.data[2] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.data[2] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
       
}


/*
void BIO_config(unsigned short data)
{
    unsigned char i, out;
    
    //CLOCK to L
    out &= 0b11111011;
    PORTC = out;
    WAIT;
    
    //RESETN to L
    out &= 0b11110111;
    PORTC = out;
    WAIT;
    
    //RESTETN to H
    out |= 0b00001000;
    PORTC = out;
    
    
    for(i = 0; i < 16; i++) {
        if (data & 0x0001) { //DATA to H
            out |= 0b00000010;
            PORTC = out;
        } else { //DATA to L
            out &= 0b11111101;
            PORTC = out;
        }        
        data >>= 1;
        
        WAIT;
        
        //CLOCK to H
        out |= 0b00000100;
        PORTC = out;
        WAIT;
        
        //CLOCK to L
        out &= 0b11111011;
        PORTC = out;       
        
    }
       
}
 */

