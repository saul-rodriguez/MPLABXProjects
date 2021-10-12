#include "comm.h"
#include "mcc_generated_files/mcc.h"



void _puts(char *pt)
{
    unsigned char index;
    index = 0;
    while(pt[index]) {
        while(!EUSART1_is_tx_ready());
        EUSART1_Write(pt[index++]);        
    }
}

void write(unsigned char *pt, unsigned char lenght)
{
    unsigned char i;
    
    for (i=0; i<lenght; i++) {
        while(!EUSART1_is_tx_ready());
        EUSART1_Write(pt[i]); 
    }    
}

void _sprintf(char *mess, unsigned short val)
{
  unsigned short aux;  
 
  //value range 0.000 - 9.999
  
  aux = val%10;
  val /= 10;  
    
  mess[5] = 0x00;
    
  mess[4] = (unsigned char)aux+'0';
    
  aux = val%10;
  val /= 10;
    
  mess[3] = (unsigned char)aux+'0';
    
  aux = val%10;
  val /= 10;
    
  mess[2] = (unsigned char)aux+'0';
  mess[1] = '.';
  mess[0] = (unsigned char)val+'0';  
}

unsigned char _gets(unsigned char *pt, unsigned char length)
{
    unsigned char index;
 //read a line
    index = 0;
    while (index < length) {
        pt[index] = EUSART1_Read();
        if (pt[index] == 0x0a) {
            index --; //uncommented only if CR+LN
            return index; 
        } 
        index++;
    } 
    
    //error, buffer Overflow
    return 0;    
}
