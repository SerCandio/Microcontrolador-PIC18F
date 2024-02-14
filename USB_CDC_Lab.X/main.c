/* 
 * File:   main.c
 * Author: CURSOS
 *
 * Created on 4 de febrero de 2024, 12:19 PM
 */

#include "RTOS.h"

#define USER_LED_Toogle()            LATDbits.LATD0=~LATDbits.LATD0

/*Task polling rate in miliseconds 'ms'*/
#define TASK1_POLLRATE_MS             1000UL 
#define TASK2_POLLRATE_MS             150UL 

/*Task Priority Order*/
#define TASK1_PRIORITY                  1U
#define TASK2_PRIORITY                  2U


/* 
 * RTOS User Tasks...
 */
void Task1(void);
void Task2(void);

/*
 * Global variables
 */
static char USB_writeBuffer[64];

/*
 * Function Prototypes
 */
void USB_CDC_Tx_String(char *s);


int main(int argc, char** argv) {
    /* 
     * Incicializaciob de perifericos
     */
    vHardwareInit();
    
    /* 
     * Creacion de Tareas RTOS + prioridades
     */
    xTaskCreate("Task 1",                       //Send "Hello World, millis= ### "
            TASK1_PRIORITY, 
            TASK1_POLLRATE_MS, 
            Task1);
    
    xTaskCreate("Task 2",                       //Toogle USER_LED  (It's a blue one!)
            TASK2_PRIORITY, 
            TASK2_POLLRATE_MS, 
            Task2);
    
    
     //Iniciar el Scheduler de ejecuacion de  tareas del RTOS........bucle while()
    vTaskStartScheduler();
    
    
    return (EXIT_SUCCESS);
}

/* 
 * RTOS User Tasks...
 */
void Task1(void){
    /* 
     * This Task will execute every : TASK1_POLLRATE_MS 
     */
    sprintf(USB_writeBuffer, "Hello World, Millis= %lu\r\n", millis());
    USB_CDC_Tx_String(USB_writeBuffer);
}

void Task2(void){
    /* 
     * This Task will execute every : TASK2_POLLRATE_MS 
     */
    
    USER_LED_Toogle();
}

/*Sub-Functions code
 */
/* 
 * Enviar un string en RAM a traves del USB-CDC
 */
void USB_CDC_Tx_String(char *s){
 //Run application code.
if(USBUSARTIsTxTrfReady()==true){
    putsUSBUSART(s);
}

}



