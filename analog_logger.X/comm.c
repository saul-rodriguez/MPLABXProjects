#include "comm.h"
#include "mcc_generated_files/mcc.h"

volatile unsigned char ADC_state;
volatile unsigned char message_format;

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
            read_analog();
            break;
            
        case 'T': //toggle between binary data or text mode
            //read_analog_mV();
            toggle_format();
            break;
            
        case 's': //start continuous analog monitoring
            start_sampling();
            break;
            
        case 'S': //stop continuous analog sampling    
            stop_sampling();
            break;
            
        default:
            break;
            
    }
}

void _puts(char *pt)
{
    unsigned char index;
    index = 0;
    while(pt[index]) {
        while(!EUSART_is_tx_ready());
        EUSART_Write(pt[index++]);        
    }
}

void write(unsigned char *pt, unsigned char lenght)
{
    unsigned char i;
    
    for (i=0; i<lenght; i++) {
        while(!EUSART_is_tx_ready());
        EUSART_Write(pt[i]); 
    }    
}

void read_analog()
{
    unsigned short adc_val;
    //unsigned char aux[2];
    unsigned long  aux1;
    char mess[6];
    
    if (ADC_state == ADC_IDLE) { //single ADC request
        adc_val = ADC_GetConversion(channel_AN2); 
    } else { //ADC_STATE = ADC_BUSY, ADC value is already converted
        adc_val = ADC_GetConversionResult();
    }
    
    if (message_format == MESSAGE_BINARY) {    
        mess[0] = (unsigned char)(adc_val & 0xff);
        mess[1] = (unsigned char)((adc_val >> 8) & 0xff);
    
        write((unsigned char*)mess,2);
    
    } else {
        //val_mv = ((unsigned long)adc_val*3300UL/1024UL); 
        aux1 = (unsigned long)adc_val*3300UL;
        adc_val = (unsigned short)(aux1 >> 10); //divides by 1024. Result is in mV
    
        _sprintf(mess,adc_val);
    
        _puts(mess);
        _puts("\n");  
    }
    
    if (ADC_state == ADC_BUSY) {
        __delay_ms(100);
        ADC_StartConversion();
    }
    
}

void _sprintf(char *mess, unsigned short val)
{
  unsigned long  aux1;
  unsigned short aux2;  
 
  //value range 0.000 - 9.999
  
  aux2 = val%10;
  val /= 10;  
    
  mess[5] = 0x00;
    
  mess[4] = (unsigned char)aux2+'0';
    
  aux2 = val%10;
  val /= 10;
    
  mess[3] = (unsigned char)aux2+'0';
    
  aux2 = val%10;
  val /= 10;
    
  mess[2] = (unsigned char)aux2+'0';
  mess[1] = '.';
  mess[0] = (unsigned char)val+'0';  
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

void start_sampling(void)
{
    if(ADC_state == ADC_IDLE) { // check if a conversion is already been triggered
        ADC_StartConversion();
        ADC_state = ADC_BUSY;
    }     
}

void stop_sampling(void)
{
    ADC_state = ADC_IDLE;
}
