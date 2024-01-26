/* 
 * File:   SoftwareUART.h
 * Author: CURSOS
 *
 * Created on 15 de noviembre de 2023, 12:38 PM
 */

#ifndef SOFTWAREUART_H
#define	SOFTWAREUART_H

#include <stdint.h>
#include "TMR2.h"               //Timer 2 for marking bits....

// Software USART pins TX, RX.........Remember to disable corresponding analog if any !!
#define SOFT_USART_PIN_TX_DIR        TRISDbits.TRISD1
#define SOFT_USART_PIN_TX            LATDbits.LATD1

/* 
 * Data Enums
 */
typedef enum{
    baudrate9600bps=80,
            baudrate4800bps=160
}baudrate_t;

/* 
 * Global variables
 * Access: Private
 */
static baudrate_t __baudrate;

/*
 * Function Prototypes
 * Access: Public
 */
extern void Software_USART_Init(baudrate_t baudrate);

extern void Software_USART_WriteChar(char data);
extern void Software_USART_WriteString(char *ptrString);

/*
 * Function Prototypes
 * Access: Private
 */
static void __software_USART_Start_Signal(void);
static void __software_USART_Stop_Signal(void);

#endif	/* SOFTWAREUART_H */

