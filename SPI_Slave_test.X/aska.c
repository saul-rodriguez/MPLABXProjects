#include "aska.h"

void ASKA_write_reg(uint8_t IC_addr ,uint8_t add, uint32_t value)
{
    uint8_t tx_buffer[5];
	
    tx_buffer[0] = add | IC_addr;
    
    tx_buffer[1] = (uint8_t)(value >> 24) & 0xff;
    tx_buffer[2] = (uint8_t)(value >> 16) & 0xff;
    tx_buffer[3] = (uint8_t)(value >> 8) & 0xff;
    tx_buffer[4] = (uint8_t)(value >> 0) & 0xff;

	//SPI_transaction(tx_buffer,5);
    CS_SetLow();    
    SPI1_WriteBlock(tx_buffer,5);
    CS_SetHigh();

}


void ASKA_test1(uint8_t ic_add)
{
        //Disable 
        //ASKA_write_reg(ic_add, ASKA_CONF1,0x00000000); 
		//new program
        /*
		ASKA_write_reg(ic_add, ASKA_ELE1,0x00008000);
		ASKA_write_reg(ic_add, ASKA_ELE2,0x00004000);
		ASKA_write_reg(ic_add, ASKA_CONF0,0x19672190);
		ASKA_write_reg(ic_add, ASKA_CONF1,0x00906420);
         */
        ASKA_write_reg(ic_add, ASKA_CONF1,0x00000000); 
		//new program
		
		ASKA_write_reg(ic_add, ASKA_CONF0,0x0a0147d0);
		ASKA_write_reg(ic_add, ASKA_CONF1,0x00907800);
        ASKA_write_reg(ic_add, ASKA_ELE1,0x00000001);
		ASKA_write_reg(ic_add, ASKA_ELE2,0x00000002);
        
}

void ASKA_test2(uint8_t ic_add)
{
        ASKA_write_reg(ic_add, ASKA_CONF1,0x00000000); 
		//new program
		
		ASKA_write_reg(ic_add, ASKA_CONF0,0x0a1727d0);
		ASKA_write_reg(ic_add, ASKA_CONF1,0x009028a0);
        ASKA_write_reg(ic_add, ASKA_ELE1,0x00000001);
		ASKA_write_reg(ic_add, ASKA_ELE2,0x00000002);
}

void ASKA_test3(uint8_t ic_add)
{
        ASKA_write_reg(ic_add, ASKA_CONF1,0x00000000); 
		//new program
		
		ASKA_write_reg(ic_add, ASKA_CONF0,0x32cb2190);
		ASKA_write_reg(ic_add, ASKA_CONF1,0x00925810);
        ASKA_write_reg(ic_add, ASKA_ELE1,0x00000001);
		ASKA_write_reg(ic_add, ASKA_ELE2,0x00000002);
}

void ASKA_test4(uint8_t ic_add)
{
        ASKA_write_reg(ic_add, ASKA_CONF1,0x00000000); 
		//new program
		
		ASKA_write_reg(ic_add, ASKA_CONF0,0x32c99190);
		ASKA_write_reg(ic_add, ASKA_CONF1,0x0090c808);
        ASKA_write_reg(ic_add, ASKA_ELE1,0x00000001);
		ASKA_write_reg(ic_add, ASKA_ELE2,0x00000002);
}
