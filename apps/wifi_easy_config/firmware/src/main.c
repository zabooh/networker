/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



#define LOG_SIZE 128
int32_t LOG_ix = 0;
uint32_t LOG_data[LOG_SIZE][3];
bool LOG_run = false;

void LOG_Start(void){
    LOG_run = true;
    LOG_data[LOG_ix][0] = CORETIMER_CounterGet();
    LOG_data[LOG_ix][1] = (uint32_t) "Start Log";
    LOG_data[LOG_ix][2] = 0;
    LOG_ix++;
    if (LOG_ix == LOG_SIZE) {
        LOG_ix = 0;
    }    
}

void LOG_Stop(void){
    LOG_run = false;

    LOG_data[LOG_ix][0] = CORETIMER_CounterGet();;
    LOG_data[LOG_ix][1] =  (uint32_t) "Stop Log";;
    LOG_data[LOG_ix][2] = 0;    
}   

void LOG_log(char *str, uint32_t data) {

    if(LOG_run == false) return;
    
    LOG_data[LOG_ix][0] = CORETIMER_CounterGet();
    LOG_data[LOG_ix][1] = (uint32_t) str;
    LOG_data[LOG_ix][2] = data;
    LOG_ix++;
    if (LOG_ix == LOG_SIZE) {
        LOG_ix = 0;
    }
}

uint32_t LOG_GetLogSize(void) {
    return LOG_SIZE;
}

void LOG_GetData(uint32_t ix, char *str) {
    int32_t ix_pre;
    int32_t delta;

    ix_pre = ix - 1;
    if (ix_pre < 0) ix_pre += LOG_SIZE;
    delta = LOG_data[ix][0] - LOG_data[ix_pre][0];

    sprintf(str, "%02d \t%09d \t%s \t%09d\n\r", ix, delta, (char*) LOG_data[ix][1], LOG_data[ix][2]);
    vTaskDelay(5 / portTICK_PERIOD_MS);
}



/*******************************************************************************
 End of File
*/

