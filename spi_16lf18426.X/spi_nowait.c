#include "spi_nowait.h"

volatile SPI_state_e SPI_state;

void SPI_nowait_initialize(void)
{
    SPI_state = SPI_IDLE;
}


void SPI1_ExchangeByte_nowait(uint8_t data)
{
    SSP1BUF = data;
    //while(!PIR3bits.SSP1IF);
    //PIR3bits.SSP1IF = 0;
    //return SSP1BUF;
    SPI_state = SPI_EXCHANGE;
}
