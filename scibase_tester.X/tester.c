#include "tester.h"
#include "mcc_generated_files/mcc.h"
#include "comm.h"
#include "bio3.h"
#include <stdio.h>

void mess_handler()
{
    unsigned char message;
    
    message = EUSART1_Read();
    
    switch (message) {        
        case 't': //test comm
            //write(message,mess_rec_size);
            _puts("Ok");
            break;
        
        case 'f': //single shot sweep measurement SE no offset, crc
            sweep();
            break;
            
        case 'a': //test ADC
            ADC_test();
            break;
    }    
}

void tester_initialize()
{
    unsigned char freq_index;
    unsigned char gain_index;
    
    VIN asic;
    
    asic.datas[0] = 0;
    asic.datas[1] = 0;
    asic.datas[2] = 0;
        
    //Initial ASIC configuration
    freq_index = 10; // Starts from 1kHz   
    gain_index = 0; // Starts with lowest gain    
    
    // Set initial gain, freq, filter
    setGain(&asic,gain_index); 
    setFreq(&asic,freq_index);
    setFilt(&asic,freq_index);
    
    asic.data_bits.IQ = 0; //Select I reference
    asic.data_bits.CE = 0; //Disable the signal generator
    config(asic); 
     __delay_ms(CONF_DELAY);
    
}

void ADC_test()
{
    unsigned short value;
    //unsigned char aux[3];
    unsigned char num;
    char sbuf[10];
    float aux;
    
    value = ADCC_GetSingleConversion(VOUT_SE);
    
    aux = (float)value*1.8/4096.0;
    
    //aux[0] = (unsigned char)((value >> 8) & 0xff);
    //aux[1] = (unsigned char)(value & 0xff);
    //aux[2] = '\n';
    
    num = sprintf(sbuf,"Vout = %3.3f V\n", aux);           
    write(sbuf,num);

}

void sweep()
{
    unsigned char gain_index;
    unsigned char freq_index;
    unsigned char i, ret, count;
    short I,Q;
    unsigned char aux[7], check;

//#ifdef BIOASIC
//    BIO3 asic;    
//    asic.datashort = 0; //Clears all bits: NS = 0 (32 steps), CE = 0 (disabled)
//#else
    VIN asic;
    asic.datas[0] = 0;
    asic.datas[1] = 0;
    asic.datas[2] = 0;
    
//#endif
    
        
    //Initial ASIC configuration
    freq_index = 10; // Starts from 1kHz   
    gain_index = 0; // Starts with lowest gain    
    setGain(&asic,gain_index); // Set initial gain
       
    //Sweep all frequencies
    for (i = 0; i < 11; i++) {
                
        setFreq(&asic,freq_index);
        setFilt(&asic,freq_index);
        
        //Measure and check if it is in range
        count = 0;
        ret = 0;
        
        do {            
        
            ret = measure(&I,&Q,asic);
            
            if (ret == 1) { //Increase Gain and repeat
                
                if (count == 2) break; // Previous decrease of gain, stops now!
                count = ret;                

                
                //if (gain_index < 7) { //for BIOASIC
                if (gain_index < 5) {  //for VIN              
                    gain_index++;
                    setGain(&asic,gain_index);
                } else {
                    break; 
                }   
                                
                continue;
                
            } else if (ret == 2) { //Decrease Gain and repeat
            
                if (count == 1) break; // Previous increase of gain, stops now!
                count = ret;
                
                if (gain_index > 0) {
                    gain_index--;
                    setGain(&asic,gain_index);
                } else {
                    break; 
                }
                
                continue;
            }
                        
        } while (ret);
         
              
        //Transmit I,Q, and current gain/freq config
        
        //merge gain and freq in one byte [freq_index : gain_index ]
        ret = (freq_index << 4) & 0xf0;
        ret |= (gain_index & 0xff);
        
        aux[0] = 'f';
        aux[1] = (unsigned char)(I & 0xff);
        aux[2] = (unsigned char)((I >> 8) & 0xff);
        aux[3] = (unsigned char)(Q & 0xff);
        aux[4] = (unsigned char)((Q >> 8) & 0xff);
        aux[5] = ret;
        
        check = calculate_checksum(aux,6);
        aux[6] = check;
        
        //TODO Here is a good idea to disable the ADC
        //ADC_OFF();
        
        //lputs_ISR(aux,7);
        write(aux,7);
        
        
        //This delay is to avoid to start a new measurement when 
        //the BT transmitter is sending.
        #ifndef BIOASIC
        __delay_ms(50);
        #endif
            
        freq_index--;
    }
    
}
    
unsigned char measure(short* I, short* Q, VIN asic)
{
    unsigned short offset, value;
    short aux1,aux2;
    //Measurements done using Single Ended output
        
    //Extract DC offset (expected value around 512 ~ 0.9V)
    asic.data_bits.IQ = 0; //Select I reference
    asic.data_bits.CE = 0; //Disable the signal generator
    config(asic); 
     __delay_ms(CONF_DELAY);
     
    //offset = ADC_5(); //read channel 5 (VOUT_SE)   
     offset = ADCC_GetSingleConversion(VOUT_SE);
    
    //extract I
    asic.data_bits.CE = 1; //Enable the signal generator
    asic.data_bits.IQ = 0; //Select I reference
    
    config(asic); 
     __delay_ms(CONF_DELAY);
     
    //value = ADC_5(); //read channel 5 (VOUT_SE)   
     value = ADCC_GetSingleConversion(VOUT_SE); 
    *I = (value - offset);
    aux1 = *I;
        
    if (aux1 < 0) {
        aux1 = -aux1;
    }
      
    
      //extract Q
    //asic.data_bits.CE = 1; //Enable the signal generator
    asic.data_bits.IQ = 1; //Select I reference
    
    config(asic); 
     __delay_ms(CONF_DELAY);
     
    value = ADCC_GetSingleConversion(VOUT_SE); 
    //value = ADC_5(); //read channel 5 (VOUT_SE)   
    *Q = (value - offset);
    aux2 = *Q;
    
    if (aux2 < 0) {
        aux2 = -aux2;
    }
    
    if (aux2 > aux1) {
        aux1 = aux2;
    }
    
    if (aux1 > MEAS_MAX) {
        return 2;
    } else if (aux1 < MEAS_MIN) {
        return 1;
    }
         
    return 0;    
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



