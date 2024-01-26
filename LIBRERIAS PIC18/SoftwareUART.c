#include "SoftwareUART.h"


extern void Software_USART_Init(baudrate_t baudrate){
    SOFT_USART_PIN_TX_DIR = 0; //Configure Softwre UART pin TX as Output ()
    SOFT_USART_PIN_TX   = 1 ;  //Set Initially HIGH.....
    
    /* Compute baudrate  : Get micrseconds delay...  bit period = 1/baudrate ...
     * 9600 bps <> 104 uS 
     * 4800 bps <> 208 uS
     * 1200 bps <> 833 uS
    */
   __baudrate = baudrate;
    
    //Init Timer 2 : 1.3uS count...no interrupts...
    Timer2_Initialize();
}

static void __software_USART_Start_Signal(void){
   SOFT_USART_PIN_TX   = 0 ;  //Set Start State : LOW.... 
}

static void __software_USART_Stop_Signal(void){
   SOFT_USART_PIN_TX   = 1 ;  //Set Stop State : HIGH....  
}

extern void Software_USART_WriteChar(char data){
    uint8_t byteData = (uint8_t) data;
    
    TMR2=0x00;                        //Reset Timer 2
    
    __software_USART_Start_Signal(); //UART START Signal
    
    Timer2_Turn_On();                // enable Timer2 module
    
    /* 
     * Compute 'bit period' delay , Timer 2 increments every 1.3uS 
     * 9600 bps <> 80 counts of 1.3uS (104uS)
     * 4800 bps <> 160 counts of 1.3uS (208uS)
     *  
     *  NOte : See enum 'baudrate_t' 
     * 
     *  OBS: 1200 bps baudrate is not supoirted by Timer 2
     */
    while(TMR2 < __baudrate  );      // Wait until bit period = 1/baudrate ...
    TMR2=0x00;                        //Reset Timer 2
    
    for(uint8_t i=0 ; i<8; i++){
        SOFT_USART_PIN_TX = byteData & 0x01 ; //Send LSB first.... D0..D1....D7
        byteData = (byteData>>1U) ;         //Shift left data
        while(TMR2 < __baudrate );           // Wait until bit period = 1/baudrate ...
        TMR2=0x00;                        //Reset Timer 2
    }
    
    Timer2_Turn_Off();        // disable Timer2 module
    
    __software_USART_Stop_Signal(); // UART Stop Signal...
    
}

extern void Software_USART_WriteString(char *ptrString){
    while(*ptrString !='\0')
    {
        Software_USART_WriteChar(*ptrString++);
    }
}
