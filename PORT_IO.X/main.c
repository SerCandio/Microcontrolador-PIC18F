/* 
 * File:   main.c
 * Author: CURSOS
 *
 * Created on 26 de enero de 2024, 03:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f45k50.h>
#include "ConfBits_RealBoardPLL.h"

#define LED_Toogle()        LATEbits.LATE0 = ~LATEbits.LATE0

/*
 * Function Prototypes
 */
static void PORT_Init(void);

int main(int argc, char** argv) {
    
    OSCILATOR_Init();
    PORT_Init();
    
    while(1)
    {  
        LED_Toogle();
        __delay_ms(1000);
          
    }

    return (EXIT_SUCCESS);
}

/* 
 * Sub - Functions code
 */
static void PORT_Init(void){
    /*Configure pin RE0 as output, disable analog and initially LOW*/
    ANSELEbits.ANSE0 = 0;
    TRISEbits.TRISE0 = 0;
    LATEbits.LATE0   = 0;
}