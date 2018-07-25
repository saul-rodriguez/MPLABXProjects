#include "comm.h"
#include "mcc_generated_files/mcc.h"

volatile unsigned char ADC_state;
volatile unsigned char message_format;

volatile unsigned char TMR1_state;

void process_message(void)
{
    unsigned char message;
    unsigned char aux[3];
    
    message = EUSART_Read();
    
    //Message handler
    switch (message) {
        case 't': //Test communications
            _puts("Ok\n");
            break;
            
        case 'a': //Ask analog value 
            //read_analog();
            ADC_value = ADC_GetConversion(channel_AN2); 
            read_analog();
            break;
            
        case 'T': //toggle between binary data or text mode
            //read_analog_mV();
            toggle_format();
            break;
            
        case 's': //start continuous analog monitoring
            if (TMR1_state == TMR1_RUNNING)
                return;
           // start_sampling();            
            TMR1_StartTimer();
            TMR1_state = TMR1_RUNNING;
            
            break;
            
        case 'S': //stop continuous analog sampling              
            
          //  stop_sampling();
            TMR1_StopTimer();
            TMR1_state = TMR1_STOP;
            break;
            
        case 'd':
            aux[0] = ADC_state+'0';
            aux[1] = 0x0d;
            write(aux,2);
            break;
            
        case 'D':
            aux[0] = TMR1_state+'0';
            aux[1] = 0x0d;
            write(aux,2);
            break;
        case 'r':
            ADCON0bits.ADON = 0;
            ADCON0bits.ADON = 1;
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
      
    //adc_val = ADC_GetConversionResult();
    adc_val = ADC_value;
    ADC_state = ADC_IDLE;
    
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
    ADC_state = ADC_BUSY; 
//    ADC_StartConversion();    
}

void stop_sampling(void)
{
    ADC_state = ADC_IDLE;
}

void _TMR1_Ready(void)
{   
    if (TMR1_state == TMR1_RUNNING) {
        ADC_value = ADC_GetConversion(channel_AN2); 
        ADC_state = ADC_READY;
    }
    
}