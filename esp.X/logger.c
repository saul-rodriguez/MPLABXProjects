#include "logger.h"
#include "mcc_generated_files/mcc.h"
#include "esp1.h"
#include "comm.h"

volatile unsigned char message_format;

volatile unsigned short ADC_value;
volatile unsigned char ADC_state;

volatile unsigned char TMR1_state;

volatile unsigned char IOC_state;
volatile unsigned char IOC_value;

void logger_initialize(void)
{
    message_format = MESSAGE_BINARY; //ADC transmitted values default to binary
      
    ADC1_SelectChannel(channel_AN2);       
    ADC_state = ADC_IDLE;
    
    TMR1_StopTimer();
    TMR1_state = TMR1_STOP;
    TMR1_SetInterruptHandler(_TMR1_Ready); //Redirect TMR1_ISR_handler to custom function
   
    //IOCA4_SetInterruptHandler()
    IOCA4_SetInterruptHandler(_IOC_Ready); //Redirect IOC in A4 to custom function
    IOC_state = IOC_IDLE;
    IOC_value = 1; // R4 has pull-up resistor enabled;
    
    ESP_Set_application_handler(process_message); // Redirect ESP RX messages to logger process_message(unsigned char);
}

void bt_message_handler(void)
{
    unsigned char message;
    message = EUSART_Read();
    process_message(message);
}

void process_message(unsigned char message)
{
       
    //Message handler
    switch (message) {
        case 't': //Test communications
            #ifdef BT
            _puts("Ok\n");            
            #else
            ESP_write("Ok\n",3);
            #endif
            break;
            
        case 'a': //Ask analog value             
            ADC_value = ADC1_GetConversion(channel_AN2); 
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
    unsigned char mess[6];
      
    adc_val = ADC_value;
    //ADC_state = ADC_IDLE; //Reset flag!
    
    if (message_format == MESSAGE_BINARY) {    
        mess[0] = (unsigned char)(adc_val & 0xff);
        mess[1] = (unsigned char)((adc_val >> 8) & 0xff);
    
        #ifdef BT
        write((unsigned char*)mess,2);
        #else
        ESP_write(mess,2);
        ESP_wait_for(ESP_SEND_OK);
        #endif
    
    } else {
        //val_mv = ((unsigned long)adc_val*3300UL/1024UL); 
        aux1 = (unsigned long)adc_val*3300UL;
        adc_val = (unsigned short)(aux1 >> 10); //divides by 1024. Result is in mV
    
        _sprintf(mess,adc_val); // Takes a value in mV and returns a string in V with 3 decimals
            
        #ifdef BT
            _puts(mess);        
            _puts("\n");
        #else
            ESP_write(mess,5);
            ESP_wait_for(ESP_SEND_OK);
        
        //IO_RA5_SetLow();
        //__delay_ms(50);
        #endif
        
    }    
    
    ADC_state = ADC_IDLE; //Reset flag!
}

void toggle_format() 
{
    if (message_format == MESSAGE_BINARY) {
        message_format = MESSAGE_TEXT;
        #ifdef BT
            _puts("tmode\n");
        #else
            ESP_write("tmode\n",6);
        #endif
    } else {
        message_format = MESSAGE_BINARY;
        #ifdef BT
            _puts("bmode\n");
        #else
            ESP_write("bmode\n",6);
        #endif
    }
}

void _TMR1_Ready(void)
{   
    if (TMR1_state == TMR1_RUNNING) {
                
#ifdef BT
        //if (ADC_state == ADC_IDLE) 
        //    ADC_state = ADC_READY; 
        ADC1_StartConversion();
#else
        //if (ADC_state == ADC_IDLE) 
        //    ADC_state = ADC_READY;         
        ADC1_StartConversion();
#endif
        
        
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
