#include "esp1.h"
#include "comm.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/eusart.h"
#include <string.h>
#include "logger.h"

volatile unsigned char esp_read_data[ESP_BUFFER_SIZE];
volatile unsigned char esp_read_data_index;
volatile unsigned char esp_channel;
volatile unsigned char esp_counter;

unsigned char ESP_read(void)
{
    unsigned char ret;
    
    esp_read_data[esp_read_data_index] = EUSART_Read();  //read 1 character   
    
    //Check if it is end of line '\n'
    if (esp_read_data[esp_read_data_index] == 0x0a) {
        //check if it is a breakline 
        if (esp_read_data_index <= 1) { //break line            
            ret =  ESP_EOL;
        } else { // it is a message, parse it
            esp_read_data[(esp_read_data_index-1)] = 0x00; //limit the string           
            ret = ESP_process_message();
        }
        
        esp_read_data_index = 0;
        return ret;
    }
    
    esp_read_data_index++;
    if (esp_read_data_index >= ESP_BUFFER_SIZE) // Reset circular buffer!
        esp_read_data_index = 0;   
    
    return ESP_OTHER;
        
}

unsigned char ESP_process_message(void) {
    unsigned char *aux;
    
    aux = strstr(esp_read_data,"SEND OK");
    if (aux) return ESP_SEND_OK;
    
    aux = strstr(esp_read_data,"OK");
    if (aux) return ESP_OK;
      
    aux = strstr(esp_read_data,"SEND FAIL");
    if (aux) return ESP_SEND_FAIL;
    
    aux = strstr(esp_read_data,"ERROR");
    if (aux) return ESP_ERROR;    
        
    aux = strstr(esp_read_data,"+IPD");
    if (aux) return ESP_RX;
    
    aux = strstr(esp_read_data,"CONNECT");
    if (aux) return ESP_CONNECT;
    
    aux = strstr(esp_read_data,"CLOSED");
    if (aux) return ESP_CLOSED;
     
    return ESP_OTHER;
}

void ESP_config(void)
{
    esp_channel = 0;    
    esp_counter = 0;
    //Check that ESP is there
    __delay_ms(250);    
    while(EUSART_is_rx_ready())
        EUSART_Read();
        
    _puts("AT\r\n");    
    ESP_wait_for(ESP_OK);
            
    //Change ESP mode to STA
    _puts("AT+CWMODE=1\r\n");
    ESP_wait_for(ESP_OK);
    
    //connect to AP
    _puts("AT+CWJAP=\"saul2\",\"rickhunter02\"\r\n");
    ESP_wait_for(ESP_OK);
    
    //Activate multiple connections
    _puts("AT+CIPMUX=1\r\n");
    ESP_wait_for(ESP_OK);
    
    //Enable server
    _puts("AT+CIPSERVER=1,80\r\n");
    ESP_wait_for(ESP_OK);
    
    
}

void ESP_wait_for(unsigned char esp_mess)
{
    unsigned char ret;
    
    
    do {
        ret = ESP_read();
        if (ret != esp_mess) { //escape exceptions
            if (ret == ESP_SEND_FAIL) return;
            if (ret == ESP_CLOSED) {
                esp_channel = 0;
                return;
            }
            if (ret == ESP_ERROR) return;
        }
    } while (ret != esp_mess);
}

void ESP_message_handler(void)
{
    unsigned char ret,aux;
    char *index;
    
    ret = ESP_read(); 
    
    switch (ret) {
        case ESP_OTHER:
            break;
            
        case ESP_RX: // Data received from the client/channel
            esp_channel = esp_read_data[5]; //Update the current channel
            index = strstr(esp_read_data,":");            
            aux = *(++index); 
                        
            //HERE call to an application message handler to consume the data
            process_message(aux);
            break;
            
        case ESP_CONNECT: // A new connection is available
            esp_channel = esp_read_data[0]; //save current channel (0-9)
            break;
            
        case ESP_CLOSED:
            esp_channel = 0;            
            break;
            
        default:
            break;
    } 
}

void ESP_write(unsigned char *pt, unsigned char length)
{
    unsigned char aux, res;
    
    _puts("AT+CIPSEND=");
    aux = esp_channel;
    write(&aux,1);
    _puts(",");
   
    aux = length;
    if (aux > 9) {
        res = aux%10;
        res += '0';
        aux /= 10;
        aux += '0';
        write(&aux,1);
        write(&res,1);
        
    } else {
        aux = length + '0';
        write(&aux,1);
    }    
    
    _puts("\r\n");
    
    ESP_wait_for(ESP_OK);
      
    write(pt,length);
    _puts("\r\n");   
    
}