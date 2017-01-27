#include "comm.h"
#include "USART1823.h"
#include "bio3.h"
#include "ADC1823.h"

volatile unsigned char mess_rec[BUFF_SIZE]; 
volatile unsigned char mess_rec_size;

void read_ADC_channels();

void mess_handler()
{
   
    
    BIO3 asic;
    
    switch (mess_rec[0]) {
        case 't': //test comm
            lputs_ISR(mess_rec,mess_rec_size);
            break;
             
        case 'c': //config
            asic.data = 0x0000;
            asic.data |= (unsigned short)(mess_rec[2]<<8);
            asic.data |= (unsigned short)(mess_rec[1]);
            
            lputs_ISR(mess_rec,mess_rec_size);
            
            BIO_config(asic);                   
            break;
            
        case 'm': //Measure ADC channels
            read_ADC_channels();
            break;
             
        default: 
            break;
    }
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
