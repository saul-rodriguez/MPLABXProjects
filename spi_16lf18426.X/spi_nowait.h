/* 
 * File:   spi_nowait.h
 * Author: saul
 *
 * Created on October 29, 2020, 1:03 PM
 */

#ifndef SPI_NOWAIT_H
#define	SPI_NOWAIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
    
typedef enum {
    SPI_IDLE,
    SPI_EXCHANGE
} SPI_state_e;

extern volatile SPI_state_e SPI_state;

void SPI_nowait_initialize(void);
void SPI1_ExchangeByte_nowait(uint8_t data);


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_NOWAIT_H */

