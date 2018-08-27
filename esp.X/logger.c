#include "logger.h"
#include "mcc_generated_files/mcc.h"
#include "esp1.h"
#include "comm.h"

volatile unsigned char message_format;

volatile unsigned short ADC_value;
volatile unsigned char ADC_state;
volatile unsigned char ADC_count;

volatile unsigned char TMR1_state;

volatile unsigned char IOC_state;
volatile unsigned char IOC_value;

volatile unsigned char WIFI_tx_buf[WIFI_TX_BUFFER_SIZE];
volatile unsigned char WIFI_tx_buf_ind;

void logger_initialize(void)
{
    message_format = MESSAGE_BINARY; //ADC transmitted values default to binary
      
    ADC1_SelectChannel(channel_AN2);       
    ADC_state = ADC_IDLE;
    ADC_value = 0;
    ADC_count = 0;
    
    TMR1_StopTimer();
    TMR1_state = TMR1_STOP;
    TMR1_SetInterruptHandler(_TMR1_Ready); //Redirect TMR1_ISR_handler to custom function
   
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
            ADC1_StartConversion();           
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
    ADC_state = ADC_IDLE; //Reset flag!
    
    if (message_format == MESSAGE_BINARY) {    
       WIFI_tx_buf[WIFI_tx_buf_ind++] = (unsigned char)(adc_val & 0xff);
       WIFI_tx_buf[WIFI_tx_buf_ind++] = (unsigned char)((adc_val >> 8) & 0xff);
            
       if (WIFI_tx_buf_ind == WIFI_TX_BUFFER_SIZE) {
            #ifdef BT
                write(WIFI_tx_buf,WIFI_TX_BUFFER_SIZE);                
            #else
                ESP_write(WIFI_tx_buf,WIFI_TX_BUFFER_SIZE);
                ESP_wait_for(ESP_SEND_OK);
            #endif
            WIFI_tx_buf_ind = 0;
       }
    } else {
        //val_mv = ((unsigned long)adc_val*3300UL/1024UL); 
        aux1 = (unsigned long)adc_val*3300UL;
        adc_val = (unsigned short)(aux1 >> 10); //divides by 1024. Result is in mV
    
        _sprintf(mess,adc_val); // Takes a value in mV and returns a string in V with 3 decimals
        mess[5] = '\n';
        #ifdef BT
            write(mess,6);           
        #else     
            ESP_write(mess,6);
            ESP_wait_for(ESP_SEND_OK);       
        #endif
        
    }    
    
    //ADC_state = ADC_IDLE; //Reset flag!
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
         ADC1_StartConversion();
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
        #ifdef BT 
            _puts("CH");
        #else
            ESP_write("CH",2);
            ESP_wait_for(ESP_SEND_OK); 
        #endif
    } else {
        #ifdef BT 
            _puts("CL");    
        #else
            ESP_write("CL",2);
            ESP_wait_for(ESP_SEND_OK); 
        #endif
    }
}


void config_wifi_settings(void)
{
    unsigned char line[16];
    unsigned char len, address, i;
        
    _puts("Logger V1.0\n");
    _puts("enter wlan name:\n");
        
    len = _gets(line,16);
    
    if (!len) {
        _puts("buffer error");
        return;
    }
            
    address = 0;
    DATAEE_WriteByte(address,len); //Save size of word
    address++;
    for (i=0; i < len; i++) {        
        DATAEE_WriteByte(address,line[i]);
        address++;
    }
    
    _puts("enter wlan password:\n");
    
    len = _gets(line,16);
    
    if (!len) {
        _puts("buffer error");
        return;
    }
    
    address = 20;
    DATAEE_WriteByte(address,len); //Save size of word
    address++;
    for (i=0; i < len; i++) {        
        DATAEE_WriteByte(address,line[i]);
        address++;
    }
    
    //Check 
    /*
    address = 0;
    for (i=0; i<14 ; i++) {
        line[i] = DATAEE_ReadByte(address);
        address++;
    }    
    write(line,14);
    */    
}

void read_wifi_settings(void)
{   unsigned char wifi[10],pass[14];    
    unsigned char i,len_wifi,len_pass,add;
    
    
    add = 0;
    len_wifi = DATAEE_ReadByte(add);
    add++;
    for (i = 0; i < len_wifi; i++) {
        wifi[i] = DATAEE_ReadByte(add);
        add++;
    }
    
    add = 20;
    len_pass = DATAEE_ReadByte(add);
    add++;
    for (i = 0; i < len_pass; i++) {
        pass[i] = DATAEE_ReadByte(add);
        add++;
    } 
      
    /*
    write(wifi,len_wifi);
    _puts("\n");
    write(pass,len_pass);
    _puts("\n");
    */
    
    ESP_config(wifi,len_wifi,pass,len_pass);
    
}


