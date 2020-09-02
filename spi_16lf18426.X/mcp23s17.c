#include "mcp23s17.h"
#include "mcc_generated_files/mcc.h"

unsigned char SPI_address;

void setAddress(unsigned char add)
{
    SPI_address = add << 1;
}

void setTrisA(unsigned char tris)
{
    SS_SetLow();
    SPI1_ExchangeByte(SPI_address);
    SPI1_ExchangeByte(MCP23017_IODIRA);
    SPI1_ExchangeByte(tris);
    SS_SetHigh();            
}

void writePortA(unsigned char val)
{
    SS_SetLow();
    SPI1_ExchangeByte(SPI_address);
    SPI1_ExchangeByte(MCP23017_GPIOA);
    SPI1_ExchangeByte(val);
    SS_SetHigh();            
}
