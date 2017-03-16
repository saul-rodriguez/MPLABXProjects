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
            
        case 'y': //Impedance without offset
            measure_Impedance_no_offset();
            break;
            
        case 'o': //Offset measurement
            measure_Offset();
            break;
            
        case 's': //impedance Measurement Single Ended 
            measure_Impedance_SE();
            break;
            
        #ifdef INDUCTIVE_POW
        case '&': //Tx loop to calibrate the reader
            calibrate_reader();
            break;
        #endif
                  
            
        default: 
            break;
    }
}

void config_ASIC()
{
#ifdef BIOASIC
    BIO3 asic;
    
   // asic.data = 0x0000;
   // asic.data |= (unsigned short)(mess_rec[2]<<8);
   // asic.data |= (unsigned short)(mess_rec[1]);
    
    asic.data[0] = mess_rec[1];
    asic.data[1] = mess_rec[2];
            
    lputs_ISR(mess_rec,mess_rec_size);
            
    BIO_config(asic);   
#else
    VIN asic;
        
    asic.data[0] = mess_rec[1];
    asic.data[1] = mess_rec[2];
    asic.data[2] = mess_rec[3];
    asic.data[3] = mess_rec[4];
    asic.data[4] = mess_rec[5];
    
    lputs_ISR(mess_rec,mess_rec_size);
    
    VIN_config(asic);
#endif
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
    
    #ifdef BIOASIC
        BIO3 asic;
    #else
        VIN asic;
    #endif
    
    
    aux[0] = 'z'; //message identifier
    
    
    #ifdef BIOASIC
    asic.data[0] = (unsigned short)(mess_rec[1]);
    asic.data[1] = (unsigned short)(mess_rec[2]);
    
    //extract Offset
    asic.data_bits.CE = 0; //Disable the signal generator
    BIO_config(asic);                   
    #else    

    asic.data[0] = mess_rec[1];
    asic.data[1] = mess_rec[2];
    asic.data[2] = mess_rec[3];
    asic.data[3] = mess_rec[4];
    asic.data[4] = mess_rec[5];
   
    asic.data_bits.CE = 0; //Disable the signal generator
    VIN_config(asic);
    #endif
    
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
    
#ifdef BIOASIC
     BIO_config(asic);                   
#else
     VIN_config(asic);
#endif
    __delay_ms(CONF_DELAY);
    
    value1 = ADC_2(); //read channel 2 (VOUT_P)     
    value2 = ADC_4(); //read channel 4 (VOUT_N)
    
    aux[5] = (unsigned char)(value1 & 0xff);
    aux[6] = (unsigned char)((value1 >> 8) & 0xff);
    aux[7] = (unsigned char)(value2 & 0xff);
    aux[8] = (unsigned char)((value2 >> 8) & 0xff);
    
    //extract Q
    asic.data_bits.IQ = 1; //Select Q reference
    
#ifdef BIOASIC
     BIO_config(asic);                   
#else
     VIN_config(asic);
#endif
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

void measure_Impedance_no_offset()
{
 unsigned char aux[13];
    unsigned short value1,value2,value3;
    
    #ifdef BIOASIC
        BIO3 asic;
    #else
        VIN asic;
    #endif
        
    aux[0] = 'y'; //message identifier
         
    #ifdef BIOASIC
        asic.data[0] = (unsigned short)(mess_rec[1]);
        asic.data[1] = (unsigned short)(mess_rec[2]);        
    #else       
        asic.data[0] = mess_rec[1];
        asic.data[1] = mess_rec[2];
        asic.data[2] = mess_rec[3];
        asic.data[3] = mess_rec[4];
        asic.data[4] = mess_rec[5];       
    #endif
           
    //extract I
     asic.data_bits.CE = 1; //Enable the signal generator
     asic.data_bits.IQ = 0; //Select I reference
    
    #ifdef BIOASIC
        BIO_config(asic);                   
    #else
        VIN_config(asic);
    #endif
    __delay_ms(CONF_DELAY);
    
    value1 = ADC_2(); //read channel 2 (VOUT_P)     
    value2 = ADC_4(); //read channel 4 (VOUT_N)
    
    aux[1] = (unsigned char)(value1 & 0xff);
    aux[2] = (unsigned char)((value1 >> 8) & 0xff);
    aux[3] = (unsigned char)(value2 & 0xff);
    aux[4] = (unsigned char)((value2 >> 8) & 0xff);
    
    //extract Q
    asic.data_bits.IQ = 1; //Select Q reference
    
    #ifdef BIOASIC
        BIO_config(asic);                   
    #else
        VIN_config(asic);
    #endif
    __delay_ms(CONF_DELAY);
    
    value1 = ADC_2(); //read channel 2 (VOUT_P)     
    value2 = ADC_4(); //read channel 4 (VOUT_N)
    
    aux[5] = (unsigned char)(value1 & 0xff);
    aux[6] = (unsigned char)((value1 >> 8) & 0xff);
    aux[7] = (unsigned char)(value2 & 0xff);
    aux[8] = (unsigned char)((value2 >> 8) & 0xff);
    
    //transmit Data
    lputs_ISR(aux,9);
}

void measure_Offset()
{
    unsigned char aux[5];
    unsigned short value1,value2;
    
    #ifdef BIOASIC
        BIO3 asic;
    #else
        VIN asic;
    #endif
    
    
    aux[0] = 'o'; //message identifier    
    
    #ifdef BIOASIC
    asic.data[0] = (unsigned short)(mess_rec[1]);
    asic.data[1] = (unsigned short)(mess_rec[2]);
    
    //extract Offset
    asic.data_bits.CE = 0; //Disable the signal generator
    BIO_config(asic);                   
    #else    

    asic.data[0] = mess_rec[1];
    asic.data[1] = mess_rec[2];
    asic.data[2] = mess_rec[3];
    asic.data[3] = mess_rec[4];
    asic.data[4] = mess_rec[5];
   
    asic.data_bits.CE = 0; //Disable the signal generator
    VIN_config(asic);
    #endif
    
    __delay_ms(CONF_DELAY);
     
    value1 = ADC_2(); //read channel 2 (VOUT_P)     
    value2 = ADC_4(); //read channel 4 (VOUT_N)
    
    aux[1] = (unsigned char)(value1 & 0xff);
    aux[2] = (unsigned char)((value1 >> 8) & 0xff);
    aux[3] = (unsigned char)(value2 & 0xff);
    aux[4] = (unsigned char)((value2 >> 8) & 0xff);
    
    //transmit Data
    lputs_ISR(aux,5);

}


void measure_Impedance_SE()
{
     unsigned char aux[13], check;
    //unsigned short value1,value2,value3;
     unsigned short value1;
    
    #ifdef BIOASIC
        BIO3 asic;
    #else
        VIN asic;
    #endif    

    #ifdef INDUCTIVE_POW
        //check checksum
        check = calculate_checksum(mess_rec,4);
        if (check) { //error detected
            aux[0] = 'e';
            lputs_ISR(aux,1);
            return;
        }
    #endif
    
    aux[0] = 's'; //message identifier    
    
    #ifdef BIOASIC
    asic.data[0] = (unsigned short)(mess_rec[1]);
    asic.data[1] = (unsigned short)(mess_rec[2]);
    
    //extract Offset
    asic.data_bits.CE = 0; //Disable the signal generator
    BIO_config(asic);                   
    #else    

    asic.data[0] = mess_rec[1];
    asic.data[1] = mess_rec[2];
    asic.data[2] = mess_rec[3];
    asic.data[3] = mess_rec[4];
    asic.data[4] = mess_rec[5];
   
    asic.data_bits.CE = 0; //Disable the signal generator
    VIN_config(asic);
    #endif
    
    __delay_ms(CONF_DELAY);
     
    value1 = ADC_5(); //read channel 5 (VOUT_SE)         
    
    aux[1] = (unsigned char)(value1 & 0xff);
    aux[2] = (unsigned char)((value1 >> 8) & 0xff);
         
    //extract I
     asic.data_bits.CE = 1; //Enable the signal generator
     asic.data_bits.IQ = 0; //Select I reference
    
#ifdef BIOASIC
     BIO_config(asic);                   
#else
     VIN_config(asic);
#endif
    __delay_ms(CONF_DELAY);
    
    value1 = ADC_5(); //read channel 5 (VOUT_SE)         
    
    aux[3] = (unsigned char)(value1 & 0xff);
    aux[4] = (unsigned char)((value1 >> 8) & 0xff);
        
    //extract Q
    asic.data_bits.IQ = 1; //Select Q reference
    
#ifdef BIOASIC
     BIO_config(asic);                   
#else
     VIN_config(asic);
#endif
    __delay_ms(CONF_DELAY);
    
    value1 = ADC_5(); //read channel 5 (VOUT_SE)     
        
    aux[5] = (unsigned char)(value1 & 0xff);
    aux[6] = (unsigned char)((value1 >> 8) & 0xff);    
    
    //transmit Data
#ifdef INDUCTIVE_POW
    check = calculate_checksum(aux,7);
    aux[7] = check;
    lputs_ISR(aux,8);
#else
    lputs_ISR(aux,7);
#endif
    
    
}

unsigned char calculate_checksum(unsigned char* data, unsigned char num)
{
    unsigned char check, i;
    
    check = 0;
    for (i = 0; i < num; i++) {
        check ^= data[i];
    }
    
    return check;     
}

void calibrate_reader()
{
    unsigned char aux[8];
    
    aux[0] = 'h';
    aux[1] = 'o';
    aux[2] = 'l';
    aux[3] = 'a';
    aux[4] = 0x00;
    aux[5] = 0xaa;
    aux[6] = 0xfe;
    aux[7] = '@';
    
    while (1) {
        CLRWDT();
         __delay_ms(250);
         lputs_ISR(aux,8);
        
    }
    
}