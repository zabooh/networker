/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    msd_app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "MSD_APP_Initialize" and "MSD_APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "MSD_APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _MSD_APP_H
#define _MSD_APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "config/pic32mz_w1_curiosity_freertos/definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
    

#define SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0 			"/dev/nvma1"
#define SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0			"/dev/mtda1"

   
    
    
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    MSD_APP_STATE_INIT=0,
    MSD_APP_STATE_START,
    MSD_APP_STATE_CHECK_SWITCH,
    MSD_APP_STATE_CHECK_FS,
    MSD_APP_STATE_MOUNT_FS,
    MSD_APP_STATE_CLEAR_DRIVE,
    MSD_APP_STATE_ERROR,
    MSD_APP_CONNECT_USB,            
    MSD_APP_STATE_SERVICE_TASKS,
    /* TODO: Define states used by the application state machine. */

} MSD_APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    MSD_APP_STATES state;
            /* USB Device Handle */
        USB_DEVICE_HANDLE usbDeviceHandle;
    /* TODO: Define any additional data used by the application. */

} MSD_APP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void MSD_APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    MSD_APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    MSD_APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void MSD_APP_Initialize ( void );


/*******************************************************************************
  Function:
    void MSD_APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    MSD_APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void MSD_APP_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _MSD_APP_H */

/*******************************************************************************
 End of File
 */

