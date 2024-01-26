#include "DHT11.h"

// send start signal to the sensor
static void __DHT11_Start_Signal(void) {
  DHT11_PIN_DIR = 0;     // configure DHT11_PIN as output
  DHT11_PIN_OUT = 0;     // clear DHT11_PIN output (logic 0)
 
  __delay_ms(25);        // wait 25 ms
  DHT11_PIN_OUT = 1;         // set DHT11_PIN output (logic 1)
 
  __delay_us(30);        // wait 30 us
  DHT11_PIN_DIR = 1;     // configure DHT11_PIN as input
}
 
// Check sensor response
static bool __DHT11_Check_Response(void) {
  TMR2=0x00;                        //Reset Timer 2

  Timer2_Turn_On();                // enable Timer2 module
 
  while(!DHT11_PIN_INPUT && TMR2 < 0x4D);  // wait until DHT11_PIN becomes high (checking of 80µs low time response)
 
  if(TMR2 > 0x4E)                     // if response time > 99µS  ==> Response error
    return 0;                        // return 0 (Device has a problem with response)
 
  else
  {
    TMR2 = 0x00;               // reset Timer2
    
    while(DHT11_PIN_INPUT && TMR2 < 0x4D); // wait until DHT11_PIN becomes low (checking of 80µs high time response)
 
    if(TMR2 > 0x4E)                   // if response time > 99µS  ==> Response error
      return 0;                      // return 0 (Device has a problem with response)
 
    else
      return 1;                      // return 1 (response OK)
  }
  
}
 
// Data read function
static bool __DHT11_Read_Data(unsigned char* dht_data)
{
  *dht_data = 0;
 
  for(char i = 0; i < 8; i++)
  {
    TMR2=0x00;                        //Reset Timer 2

    while(!DHT11_PIN_INPUT)      // wait until DHT11_PIN becomes high
      if(TMR2 > 0x4D) {    // if low time > 100  ==>  Time out error (Normally it takes 50µs)
        return 1;
      }
    
    TMR2=0x00;                        //Reset Timer 2
 
    while(DHT11_PIN_INPUT)       // wait until DHT11_PIN becomes low
      if(TMR2 > 0x4D) {    // if high time > 100  ==>  Time out error (Normally it takes 26-28µs for 0 and 70µs for 1)
        return 1;          // return 1 (timeout error)
      }
 
     if(TMR2 > 0x27)                  // if high time > 50  ==>  Sensor sent 1
       *dht_data |= (1 << (7 - i));  // set bit (7 - i)
  }
 
  return 0;                          // return 0 (data read OK)
}

extern void DHT11_Init(void){       //Configures Timer 2
    /*
     * Iniciar Timer 2, a 1.3us de cuenta (max 255), sin interrupciones
     */
    Timer2_Initialize();        //Initially Timer 2 is Off
}

extern void DHT11_Read_Temperature_Humidity(dht11_data_t *pdht11Data, dht11_Error_Flags_t *pdht11_Error_Flags){
     unsigned char T_Byte1, T_Byte2, RH_Byte1, RH_Byte2, CheckSum ;
     
      /*Clear all error flags-...*/
      pdht11_Error_Flags->checkSumError=false;
      pdht11_Error_Flags->responseError=false;
      pdht11_Error_Flags->timeoutError=false;
   
    __DHT11_Start_Signal();     // send start signal to the sensor
 
    if(__DHT11_Check_Response())    // check if there is a response from sensor (If OK start reading humidity and temperature data)
    {
      // read (and save) data from the DHT11 sensor and check time out errors
      if(__DHT11_Read_Data(&RH_Byte1) || __DHT11_Read_Data(&RH_Byte2) || __DHT11_Read_Data(&T_Byte1) || __DHT11_Read_Data(&T_Byte2) || __DHT11_Read_Data(&CheckSum))
      {
        //return true;        //Timeout error
          pdht11_Error_Flags->timeoutError=true;
      }
 
      else         // if there is no time out error
      {
        if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF))   // if there is no checksum error
        {     
            /*If no errors, then display data...*/
          /*Output Temperature data with units C*/
          pdht11Data->ptemperature[0]=T_Byte1 / 10  + '0';
          pdht11Data->ptemperature[1]=T_Byte1 % 10  + '0';
          pdht11Data->ptemperature[2]='.';
          pdht11Data->ptemperature[3]=T_Byte2 / 10  + '0';
          pdht11Data->ptemperature[4]=' ';
          pdht11Data->ptemperature[5]='°';    // put degree symbol (°)
          pdht11Data->ptemperature[6]='C'; 
          
          /*Output Humidity data with units %*/
          pdht11Data->phumidity[0]=RH_Byte1 / 10 + '0';
          pdht11Data->phumidity[1]=RH_Byte1 % 10 + '0';
          pdht11Data->phumidity[2]='.';
          pdht11Data->phumidity[3]=RH_Byte2 / 10 + '0';
          pdht11Data->phumidity[4]=' ';
          pdht11Data->phumidity[5]='%';
        }
        
        // if there is a checksum error
        else
        {  
          pdht11_Error_Flags->checkSumError=true;
          //return true;
        }
        
      }
      
    }
 
    // if there is a response (from the sensor) problem
    else
    {
        pdht11_Error_Flags->responseError=true;
       // return true;
    }
    
    Timer2_Turn_Off();        // disable Timer2 module
    
}
