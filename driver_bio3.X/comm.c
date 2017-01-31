#include "comm.h"
#include "USART1823.h"
#include "bio3.h"
#include "ADC1823.h"

volatile unsigned char mess_rec[BUFF_SIZE]; 
volatile unsigned char mess_rec_size;



void mess_handler()
{
       
    //BIO3 asic;
    
    switch (mess_rec[0]) {
        case 't': //test comm
            lputs_ISR(mess_rec,mess_rec_size);
            break;
             
        case 'c': //config            
            config_ASIC();
            break;
            
        case 'm': //Measure ADC channels
            read_ADC_channels();
            break;
        
        case 'z': //Impedance Measurement
            measure_Impedance();
            break; 
            
        default: 
            break;
    }
}

void config_ASIC()
{
    BIO3 asic;
    
    asic.data = 0x0000;
    asic.data |= (unsigned short)(mess_rec[2]<<8);
    asic.data |= (unsigned short)(mess_rec[1]);
            
    lputs_ISR(mess_rec,mess_rec_size);
            
    BIO_config(asic);                   
}

void read_ADC_channels()
{
     unsigned char aux[7];
     unsigned short value1,value2,value3;
    
     //read channel 2 (VOUT_P)
     value1 = ADC_2();
     //read channel 4 (VOUT_N)
     value2 = ADC_4();
     //read channel 5 (VOUT SE)
     value3 = ADC_5();
     ADC_OFF();
     
     aux[0] = 'm';
     aux[1] = (unsigned char)(value1 & 0xff);
     aux[2] = (unsigned char)((value1 >> 8) & 0xff);
     aux[3] = (unsigned char)(value2 & 0xff);
     aux[4] = (unsigned char)((value2 >> 8) & 0xff);
     aux[5] = (unsigned char)(value3 & 0xff);
     aux[6] = (unsigned char)((value3 >> 8) & 0xff);
     
      lputs_ISR(aux,7);
}

void measure_Impedance()
{
    unsigned char aux[13];
    unsigned short value1,value2,value3;
    BIO3 asic;
    
    aux[0] = 'z'; //message identifier
    
    asic.data = 0x0000;
    asic.data |= (unsigned short)(mess_rec[2]<<8);
    asic.data |= (unsigned short)(mess_rec[1]);
    
    //extract Offset
    asic.data_bits.CE = 0; //Disable the signal generator
    BIO_config(asic);                   
    __delay_ms(CONF_DELAY);
     
    value1 = ADC_2(); //read channel 2 (VOUT_P)     
    value2 = ADC_4(); //read channel 4 (VOUT_N)
    
    aux[1] = (unsigned char)(value1 & 0xff);
    aux[2] = (unsigned char)((value1 >> 8) & 0xff);
    aux[3] = (unsigned char)(value2 & 0xff);
    aux[4] = (unsigned char)((value2 >> 8) & 0xff);
     
    //extract I
     asic.data_bits.CE = 1; //Enable the signal generator
     asic.data_bits.IQ = 0; //Select I reference
    
     BIO_config(asic);                   
    __delay_ms(CONF_DELAY);
    
    value1 = ADC_2(); //read channel 2 (VOUT_P)     
    value2 = ADC_4(); //read channel 4 (VOUT_N)
    
    aux[5] = (unsigned char)(value1 & 0xff);
    aux[6] = (unsigned char)((value1 >> 8) & 0xff);
    aux[7] = (unsigned char)(value2 & 0xff);
    aux[8] = (unsigned char)((value2 >> 8) & 0xff);
    
    //extract Q
    asic.data_bits.IQ = 1; //Select Q reference
    
     BIO_config(asic);                   
    __delay_ms(CONF_DELAY);
    
    value1 = ADC_2(); //read channel 2 (VOUT_P)     
    value2 = ADC_4(); //read channel 4 (VOUT_N)
    
    aux[9] = (unsigned char)(value1 & 0xff);
    aux[10] = (unsigned char)((value1 >> 8) & 0xff);
    aux[11] = (unsigned char)(value2 & 0xff);
    aux[12] = (unsigned char)((value2 >> 8) & 0xff);
    
    //transmit Data
    lputs_ISR(aux,13);
}