#include "nn2sense.h"
#include "mcc_generated_files/mcc.h"

#define WAIT __delay_ms(1);
//#define WAIT __delay_us(5);

volatile NN2SENSE nn2s;

void NN2SENSE_setup(void)
{
    nn2s.data = 0;
    
    RESETN_SetHigh();
    CLK_SetLow();
    DAT_SetLow();
}

void NN2SENSE_config(NN2SENSE conf)
{
    unsigned char i, out;
    
    CLK_SetLow();
    WAIT;
    
    RESETN_SetLow();
    WAIT;
    
    RESETN_SetHigh();
    WAIT;
    
    for (i = 0; i < NN2SENSE_LENGTH; i++) {
        if (conf.data & 0x0001) { // dat to high
            DAT_SetHigh();
        } else { // dat to low
            DAT_SetLow();            
        }
        
        conf.data >>= 1;
        
        WAIT;
        
        CLK_SetHigh();
        WAIT;
        CLK_SetLow();
        
    }    
    
}

void NN2SENSE_setDAC(unsigned char dac)
{
    DAC aux;
    aux.data = dac;
    
    nn2s.bits.DAC0 = aux.bits.DAC0;
    nn2s.bits.DAC1 = aux.bits.DAC1;
    nn2s.bits.DAC2 = aux.bits.DAC2;
    nn2s.bits.DAC3 = aux.bits.DAC3;        
}


void NN2SENSE_setSEL(unsigned char sel)
{
    SEL aux;
    aux.data = sel;
    
    nn2s.bits.SEL0 = aux.bits.SEL0;
    nn2s.bits.SEL1 = aux.bits.SEL1;
    nn2s.bits.SEL2 = aux.bits.SEL2;
    nn2s.bits.SEL3 = aux.bits.SEL3;        
    nn2s.bits.SEL4 = aux.bits.SEL4;            
}