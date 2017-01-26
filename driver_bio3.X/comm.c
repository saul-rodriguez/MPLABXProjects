#include "comm.h"
#include "USART1823.h"
#include "bio3.h"

volatile unsigned char mess_rec[BUFF_SIZE]; 
volatile unsigned char mess_rec_size;

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
            
            break;
             
        default: 
            break;
    }
}