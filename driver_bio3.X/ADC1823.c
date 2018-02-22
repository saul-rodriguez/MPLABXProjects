#include "ADC1823.h"

void setup_ADC()
{
    // A/D configuration. The converter module is not turned on here.
    
    /* NOTE: ANSELA, ANSELC should be configured either here or in a general configuration function at startup!
     * (page 125,129)
     *
     * Example:
     * ANSELA = 0x04; // Only Pin RA2 configured as analog (AN_2)
     * ANSELC = 0x07; // Pin C0,C1,C2 configured as analog    
     * ANSELC = 0b11110001; // Only Pin RC0 configured as analog (AN_4)
     * 
     */

  //ADCON1 = 0b01000000; // Left justified, Fosc/4, VREF+ = VDD (page 146)
  //ADCON1 = 0b11000000; // Right justified, Fosc/4, VREF+ = VDD (page 146)
  //ADCON1 = 0b01110000; // Left justified, FRC, VREF+ = VDD (page 146)
    ADCON1 = 0b11110000; // Right justified, FRC, VREF+ = VDD (page 146)
    ADC_OFF();           // No channel selected, ADC disabled
    
}

unsigned short ADC_2()
{
    unsigned short ADC_value;

    SEL_CH2();
    NOP();
    //NOP();
    //NOP();
    //NOP();
    ADC_GO();
    return ADC_value;
}

unsigned short ADC_4()
{
    unsigned short ADC_value;

    SEL_CH4();
    NOP();
    ADC_GO();
    return ADC_value;
}

unsigned short ADC_5()
{
    unsigned short ADC_value;

    SEL_CH5();
    NOP();
    ADC_GO();
  //  ADC_OFF()
    return ADC_value;
}

unsigned short ADC_6()
{
    unsigned short ADC_value;

    SEL_CH6();
    NOP();
    ADC_GO();
    return ADC_value;
}

//void ADC_OFF() // Turns off the converter module (defined as a macro)
