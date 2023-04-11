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

#define LOG_DATA
#ifdef LOG_DATA
#define LOG_SIZE 64
int32_t LOG_ix = 0;
uint32_t LOG_data[LOG_SIZE][4];
bool LOG_run = false;

void LOG_Start(void);
void LOG_Stop(void);
void LOG_log(char *str, uint32_t data_1, uint32_t data_2);
uint32_t LOG_GetLogSize(void);
void LOG_GetData(uint32_t ix, char *str);


void LOG_Start(void){
    LOG_run = true;
    LOG_data[LOG_ix][0] = CORETIMER_CounterGet();
    LOG_data[LOG_ix][1] = (uint32_t) "Start";
    LOG_data[LOG_ix][2] = 0;
    LOG_data[LOG_ix][3] = 0;
    LOG_ix++;
    if (LOG_ix == LOG_SIZE) {
        LOG_ix = 0;
    }    
}

void LOG_Stop(void){
    LOG_run = false;

    LOG_data[LOG_ix][0] = CORETIMER_CounterGet();;
    LOG_data[LOG_ix][1] =  (uint32_t) "Stop";;
    LOG_data[LOG_ix][2] = 0;    
    LOG_data[LOG_ix][3] = 0;    
}   

void LOG_log(char *str, uint32_t data_1, uint32_t data_2) {

    if(LOG_run == false) return;
    
    LOG_data[LOG_ix][0] = CORETIMER_CounterGet();
    LOG_data[LOG_ix][1] = (uint32_t) str;
    LOG_data[LOG_ix][2] = data_1;
    LOG_data[LOG_ix][3] = data_2;
    LOG_ix++;
    if (LOG_ix == LOG_SIZE) {
        LOG_ix = 0;
    }
}

uint32_t LOG_GetLogSize(void) {
    return LOG_ix;
}

void LOG_GetData(uint32_t ix, char *str) {
    int32_t ix_pre;
    int32_t delta;

    ix_pre = ix - 1;
    if (ix_pre < 0) ix_pre += LOG_SIZE;
    delta = LOG_data[ix][0] - LOG_data[ix_pre][0];
    if(delta<0)delta=0;
    sprintf(str, "%02d %09d %08x %08x %s", ix, delta , LOG_data[ix][2], LOG_data[ix][3],(char*)LOG_data[ix][1] );    
}
#endif


/*******************************************************************************
 End of File
*/

