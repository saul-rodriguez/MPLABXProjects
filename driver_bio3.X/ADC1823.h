#ifndef ADC1823_H
#define ADC1823_H

#include <xc.h>

#define ADC_GO() {  ADGO = 1;\
                    while (ADGO);\
                    ADC_value = ADRESH;\
                    ADC_value <<= 8;\
                    ADC_value |= ADRESL;}

// Select channel X, !done, and enable ADC (page 145)
#define SEL_CH2() { ADCON0 = 0b00001001;}
#define SEL_CH4() { ADCON0 = 0b00010001;}
#define SEL_CH5() { ADCON0 = 0b00010101;}
#define SEL_CH6() { ADCON0 = 0b00011001;}

// disconnects the channels and disables the ADC module
#define ADC_OFF() { ADCON0 = 0b00100100;}  

void setup_ADC();
unsigned short ADC_2();
unsigned short ADC_4();
unsigned short ADC_5();
unsigned short ADC_6();


#endif