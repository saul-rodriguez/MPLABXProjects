#include "logger.h"
#include "comm.h"
#include "mcc_generated_files/mcc.h"

volatile unsigned short ADC_value;
volatile unsigned char ADC_state;
volatile unsigned char message_format;

volatile unsigned char TMR1_state;
volatile unsigned char IOC_state;
volatile unsigned char IOC_value;


void process_message(void)
{
    unsigned char message;
       
    message = EUSART_Read();
    
    //Message handler
    switch (message) {
        case 't': //Test communications
            _puts("Ok\n");
            break;
            
        case 'a': //Ask analog value             
            ADC_value = ADC_GetConversion(channel_AN2); 
            read_analog();
            break;
            
        case 'T': //toggle between binary data or text mode           
            toggle_format();
            break;
            
        case 's': //start continuous analog monitoring
            if (TMR1_state == TMR1_RUNNING)
                return;                     
            TMR1_StartTimer();
            TMR1_state = TMR1_RUNNING;
            
            break;
            
        case 'S': //stop continuous analog sampling              
                    
            TMR1_StopTimer();
            TMR1_state = TMR1_STOP;
            break;
                           
        case 'o': // Change digital output to low 
            
            IO_RA5_SetLow();
            break;
            
        case 'O': // Change digital output to high
            
            IO_RA5_SetHigh();
            break;
                        
        default:
            break;            
    }
}

void read_analog()
{
    unsigned short adc_val;
    //unsigned char aux[2];
    unsigned long  aux1;
    char mess[6];
      
    adc_val = ADC_value;
    ADC_state = ADC_IDLE; //Reset flag!
    
    if (message_format == MESSAGE_BINARY) {    
        mess[0] = (unsigned char)(adc_val & 0xff);
        mess[1] = (unsigned char)((adc_val >> 8) & 0xff);
    
        write((unsigned char*)mess,2);
    
    } else {
        //val_mv = ((unsigned long)adc_val*3300UL/1024UL); 
        aux1 = (unsigned long)adc_val*3300UL;
        adc_val = (unsigned short)(aux1 >> 10); //divides by 1024. Result is in mV
    
        _sprintf(mess,adc_val); // Takes a value in mV and returns a string in V with 3 decimals
    
        _puts(mess);
        _puts("\n");  
    }    
}

void toggle_format() 
{
    if (message_format == MESSAGE_BINARY) {
        message_format = MESSAGE_TEXT;
        _puts("tmode\n");
    } else {
        message_format = MESSAGE_BINARY;
        _puts("bmode\n");
    }
}

void _TMR1_Ready(void)
{   
    if (TMR1_state == TMR1_RUNNING) {
        ADC_value = ADC_GetConversion(channel_AN2); 
        ADC_state = ADC_READY;        
    }    
}

void _IOC_Ready(void)
{
    //__delay_ms(2); //Timeout for filter bouncing/noise    
    IOC_value = IO_RA4_GetValue();    
    IOC_state = IOC_READY;
        
}

void process_ioc(void)
{
    IOC_state = IOC_IDLE;
     if (IOC_value) {
        _puts("CH");
    } else {
        _puts("CL");    
    }
}
