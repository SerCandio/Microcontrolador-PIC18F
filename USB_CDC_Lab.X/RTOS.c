#include "RTOS.h"

//Funcion para agregar tareas a la lista
extern uint8_t xTaskCreate(const char *pcName, uint16_t xPriority, const uint32_t pvTaskRateMs, void (*pvTaskCode)(void)){
    uint8_t i=1;
    uint8_t ret =0;
//    TCB_t temp;
    
//    int length = sizeof(taskList)/sizeof(taskList[0]) ; 
    
    printf("Creando Tarea\r\n");
    
    while(i <=MAX_NUM_TASKS)
    {
        if(strlen(pcName) > MAX_NAME_LEN)
        {
            printf("Error -> Nombre de la Tarea muy grande\r\n");
            return ret;
        }
        
        if (taskList[i].taskInList != 1)
        {
            printf("Tarea creada #: %d\r\n\r\n", i);
            taskList[i].tID =i;
            strcpy(taskList[i].nameTask,pcName);
            taskList[i].priority = xPriority;
            taskList[i].tPollRateMs = pvTaskRateMs;
            taskList[i].tElapsedMs = millis(); 
            taskList[i].pvFuncTask=pvTaskCode;
            taskList[i].taskInList =1;
            ret =1;
            break;
        }
        i++; //Si el espacio ya esta reservado, incrementa a otro
        
    }
        
    return ret ; 
    
}

//Implementacion basica de un scheduler
/*No se toma en cuenta la prioridad*/
extern void vTaskStartScheduler(void){
    uint16_t i = 1;
    void (*pvTask) (void);
    int length = sizeof(taskList)/sizeof(taskList[0]) ; 
    TCB_t temp;
    
    /*  
     * Reordenar la lista de tareas segun si prioridad. 
     * Nota: Numero 'priority' mas bajo tiene prioridad de ejecucion mas alta
     */
    for (int j = 0; j <=length; j++) {     
        for (int k = j+1; k <=length; k++) {     
           if(taskList[j].priority > taskList[k].priority) {    
               temp = taskList[j];    
               taskList[j] = taskList[k];    
               taskList[k] = temp;    
           }     
        }     
    }  
    
    /* 
     * Mostrar el orden de ejecucion de las tareas, solo si el modo DEBUG habilitado
     */
#if defined(TASK_DEBUG_MODE)
    for(i = 1; i<=MAX_NUM_TASKS; i++)
    {
         printf("\r\n%s ,order: %u", taskList[i].nameTask, taskList[i].priority);
    }
    puts("\r\n\r\n");
#endif
    
    while(1)
    {
        
     USBDeviceTasks();

     if((USBGetDeviceState() < CONFIGURED_STATE) ||(USBIsDeviceSuspended() == true))
    {
        //Either the device is not configured or we are suspended
        //  so we don't want to do execute any application code
        continue;   //go back to the top of the while loop
    }else
    {
         
         //Keep trying to send data to the PC as required
         CDCTxService();
         
        for(i = 0; i<=MAX_NUM_TASKS; i++)
        {
            if(taskList[i].taskInList ==1)
            {
                if(millis()>=(taskList[i].tElapsedMs + taskList[i].tPollRateMs))
                {
                    taskList[i].tElapsedMs = millis();
#if defined(TASK_DEBUG_MODE)
                    printf("\r\n%s ,order: %u", taskList[i].nameTask, taskList[i].priority);
#endif
                    pvTask = (void *) taskList[i].pvFuncTask;
                    (*pvTask) (); //Llalmado indirecto a funcion de la tarea
                }
                
            }
            
        }  
         
#if defined(SLEEP_MODE)
        asm("SLEEP");
        asm("NOP");
#endif
         
    }
        
        
    }
}

//INCIO DE PERIFERICOS DE HARDWARE
extern void vHardwareInit(void){
    
    //48 MHz System Clock FOSC..........................OK
    OSCILATOR_Init();

    //Iniciar Pines I/O
    PORT_Init();
    
    //Iniciar Timer 2 ...
    /*1.3 uS resolution*/
    Timer2_Initialize();
    
    //Init USB CDC Port.............call any baudrate !!!
    USBDeviceInit();
    USBDeviceAttach();
    
    // Iniciar millis() , con su interrupcion por Timer 1 (cada 1ms) a Alta  prioridad
    Millis_Init(true);
    
    //Inciiar interrucpiones de perifericos
    INTERRUUPT_Init();
   
}

//Implementacion de delay de Task, Power Saving
extern void vTaskDelay(uint32_t taskDelayMs){
    uint32_t start=millis();
    
    while((millis() - start)<=taskDelayMs){
        /* Sleep mode only works on a Real Board, otherwise crashes simulation
         * Once "1ms" interrupt occurs(Timer 1), wakes up processor. This saves power
         */
#if defined(SLEEP_MODE)
        asm("SLEEP");
        asm("NOP");
#endif
        
    }
}

//Implementacion de funcion "printf" 
//Redireccionable a puerto USB - CDC
void  putch(char c){
    char ch[1];
    
    ch[0] = c & 0xFF ;
    
    if(USBUSARTIsTxTrfReady())
    {
        putsUSBUSART(ch);
    }
      
 
}

/* 
 * I/O Ports.....
 */
static void PORT_Init(void){
    /* 
     * RC0 y RC1 ya no estan disponibles !!  : Timer 1 / Secondary Oscilator
    */
    
    /*Enable RD0 as digital output and initially LOW*/
    ANSELDbits.ANSD0 =0;
    TRISDbits.TRISD0=0;
    LATDbits.LATD0 =0;
    
}
