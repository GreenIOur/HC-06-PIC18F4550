/* 
 * File:   UART.h
 * Author: pandor
 *
 * Created on 10 septembre 2015, 19:21
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <p18f4550.h>
#include <xc.h>
    
extern char reception[100];
extern char ii;

void init_uart(void);

/*Interruption*/
void interrupt SerialRxPinInterrupt(void);



#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

