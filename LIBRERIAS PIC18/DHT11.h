/* 
 * File:   DHT11.h
 * Author: CURSOS
 *
 * Created on 10 de noviembre de 2023, 07:57 PM
 */

#ifndef DHT11_H
#define	DHT11_H

#include <xc.h>
#include <stdbool.h>
#include "ConfBits_RealBoardPLL.h"
#include "TMR2.h"

// DHT11 sensor connection (here data pin is connected to RB0)
#define DHT11_PIN_OUT      LATBbits.LATB4                           //Remebmber to Disable AN11!!
#define DHT11_PIN_INPUT    PORTBbits.RB4                        //For input signal
#define DHT11_PIN_DIR      TRISBbits.TRISB4

/* 
 * Data structures
 * Copy member '..._t' on your code
 */
typedef struct{
    unsigned char ptemperature[8];
    unsigned char phumidity[8];
}dht11_data_t;                      //For retreiving sensor data

typedef struct{
    bool responseError;
    bool timeoutError;
    bool checkSumError;
    
}dht11_Error_Flags_t;

/* 
 * Function Prototypes
 * Access : Private   ............Do not access!!
 */
static void __DHT11_Start_Signal(void);
static bool __DHT11_Check_Response(void);
static bool __DHT11_Read_Data(unsigned char* dht_data);

/* 
 * Function Prototypes
 * Access : Public ............ Call this function only
 */
extern void DHT11_Init(void);                           //Configures & Initializes Timer 2 to 1.3uS count
extern void DHT11_Read_Temperature_Humidity(dht11_data_t *pdht11Data, dht11_Error_Flags_t *pdht11_Error_Flags);


#endif	/* DHT11_H */

