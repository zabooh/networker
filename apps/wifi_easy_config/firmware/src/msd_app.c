/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    msd_app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "msd_app.h"
#include "bsp/bsp.h"
#include "config/pic32mz_w1_curiosity_freertos/definitions.h"
#include "string.h"
#include "system/fs/sys_fs.h"
#include "system/command/sys_command.h"
#include "app_mqtt.h"

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the MSD_APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

MSD_APP_DATA msd_appData;

bool mqtt_init_flag = false;

uint8_t CACHE_ALIGN work[SYS_FS_FAT_MAX_SS];

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define CMD_MSG(x) (*pCmdIO->pCmdApi->msg)(cmdIoParam, x) 

static void my_pub(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc == 2) {
        APP_MQTT_PublishMsg(argv[1]);
        CMD_MSG("Publish MQTT Message: ");
        CMD_MSG(argv[1]);
        CMD_MSG("\n\r");
    }
    else
    {
        CMD_MSG("Wrong Parameter Number\r\n");
    }
}

static void my_connect(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc == 1) {
        CMD_MSG("Connect to Default MQTT Broker: ");
        CMD_MSG(SYS_MQTT_INDEX0_BROKER_NAME);
        CMD_MSG("\n\r");
        APP_MQTT_Initialize();
        mqtt_init_flag = true;
    } else if (argc == 2) {
        strcpy(g_sSysMqttConfig.sBrokerConfig.brokerName, argv[1]);
        CMD_MSG("Connect to MQTT Broker: ");
        CMD_MSG(argv[1]);
        CMD_MSG("\n\r");
        APP_MQTT_Initialize();
        mqtt_init_flag = true;
    } else if (argc == 3) {
        strcpy(g_sSysMqttConfig.sBrokerConfig.brokerName, argv[1]);
        strcpy(g_sSysMqttConfig.sSubscribeConfig[0].topicName, argv[2]);
        CMD_MSG("Connect to MQTT Broker: ");
        CMD_MSG(argv[1]);
        CMD_MSG("with topic: ");
        CMD_MSG(argv[2]);
        CMD_MSG("\n\r");
        APP_MQTT_Initialize();
        mqtt_init_flag = true;
    } else {
        CMD_MSG("Wrong Parameter Number\r\n");
    }
}

const SYS_CMD_DESCRIPTOR msd_cmd_tbl[] = {
    {"pub", (SYS_CMD_FNC) my_pub, ": Publish MQTT Message: pub msg "},
    {"con", (SYS_CMD_FNC) my_connect, ": Connect to MQTT Broker: con [host] [topic]"},
};

static bool MSD_CMDInit(void) {
    bool ret = false;

    if (!SYS_CMD_ADDGRP(msd_cmd_tbl, sizeof (msd_cmd_tbl) / sizeof (*msd_cmd_tbl), "apps", ": Application Commands")) {
        ret = true;
    }
    return ret;
}



// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
 */


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event, void * pEventData, uintptr_t context) {
    /* This is an example of how the context parameter
       in the event handler can be used.*/

    MSD_APP_DATA * appData = (MSD_APP_DATA*) context;

    switch (event) {
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:

            /* Device was reset or de-configured. Update LED status */
            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Device is configured. Update LED status */
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            break;

        case USB_DEVICE_EVENT_POWER_DETECTED:

            /* VBUS is detected. Attach the device. */
            USB_DEVICE_Attach(appData->usbDeviceHandle);
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:

            /* VBUS is not detected. Detach the device */
            USB_DEVICE_Detach(appData->usbDeviceHandle);
            break;

            /* These events are not used in this demo */
        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        case USB_DEVICE_EVENT_SOF:
        default:
            break;
    }
}

static bool checkFSMount() {

    if (SYS_FS_Mount(SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0, TCPIP_HTTP_WEB_DIR, FAT, 0, NULL) == SYS_FS_RES_SUCCESS) {
        return true;
    } else {
        return false;
    }

}

/*******************************************************************************
  Function:
    void MSD_APP_Initialize ( void )

  Remarks:
    See prototype in msd_app.h.
 */

void MSD_APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    msd_appData.state = MSD_APP_STATE_INIT;

    /* Set device layer handle as invalid */
    msd_appData.usbDeviceHandle = USB_DEVICE_HANDLE_INVALID;

    MSD_CMDInit();
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void MSD_APP_Tasks ( void )

  Remarks:
    See prototype in msd_app.h.
 */


SYS_FS_HANDLE dirHandle;
SYS_FS_FSTAT stat;
SYS_FS_HANDLE fileHandle;
            
void MSD_APP_Tasks(void) {
    SYS_FS_FORMAT_PARAM opt;

    {
        static MSD_APP_STATES state = -1;
        if (state != msd_appData.state) {
            switch (msd_appData.state) {
                case MSD_APP_STATE_INIT: SYS_CONSOLE_PRINT("MSD_APP_STATE_INIT\r\n");
                    break;
                case MSD_APP_STATE_CHECK_SWITCH: SYS_CONSOLE_PRINT("MSD_APP_STATE_CHECK_SWITCH\r\n");
                    break;
                case MSD_APP_STATE_CHECK_FS: SYS_CONSOLE_PRINT("MSD_APP_STATE_CHECK_FS\r\n");
                    break;
                case MSD_APP_STATE_MOUNT_FS: SYS_CONSOLE_PRINT("MSD_APP_STATE_MOUNT_FS\r\n");   
                    break;
                case MSD_APP_STATE_CLEAR_DRIVE: SYS_CONSOLE_PRINT("MSD_APP_STATE_CLEAR_DRIVE\r\n");
                    break;
                case MSD_APP_STATE_ERROR: SYS_CONSOLE_PRINT("MSD_APP_STATE_ERROR\r\n");
                    break;
                case MSD_APP_CONNECT_USB: SYS_CONSOLE_PRINT("MSD_APP_CONNECT_USB\r\n");
                    break;
                case MSD_APP_STATE_SERVICE_TASKS: SYS_CONSOLE_PRINT("MSD_APP_STATE_SERVICE_TASKS\r\n");
                    break;
                default: SYS_CONSOLE_PRINT("MSD_APP_STATE Unknown\r\n");
                    break;
            }
        }
        state = msd_appData.state;
    }

    /* Check the application's current state. */
    switch (msd_appData.state) {
            /* Application's initial state. */
        case MSD_APP_STATE_INIT:
        {
            bool appInitialized = true;
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            if (appInitialized) {
                SYS_CONSOLE_PRINT("MSD_APP_Tasks Started\r\n");
                msd_appData.state = MSD_APP_STATE_MOUNT_FS; 
            }
            break;
        }

        case MSD_APP_STATE_MOUNT_FS:
            if (checkFSMount()) {
                msd_appData.state = MSD_APP_STATE_CHECK_FS;
            }
            break;

        case MSD_APP_STATE_CHECK_FS:
            if (SYS_FS_ERROR_NO_FILESYSTEM == SYS_FS_Error()) {
                msd_appData.state = MSD_APP_STATE_CLEAR_DRIVE;
            }

            dirHandle = SYS_FS_DirOpen("/mnt/mchpSite1/");

            if (dirHandle != SYS_FS_HANDLE_INVALID) {
               SYS_CONSOLE_PRINT("FS:Directory open is successful\r\n");               
            }
            
            LOG_Start();
            do {                
                LOG_log("Read Dir",0);
                if (SYS_FS_DirRead(dirHandle, &stat) == SYS_FS_RES_FAILURE) {
                    SYS_CONSOLE_PRINT("FS:Directory read failed\r\n");
                } else {
                    if(stat.fname[0] == '\0') break;
                    SYS_CONSOLE_PRINT("FS:%s\n\r", stat.fname);             
                }                
            } while (1);
            LOG_Stop();
                    
            fileHandle = SYS_FS_FileOpen("/mnt/mchpSite1/index.htm", (SYS_FS_FILE_OPEN_READ));
            if (fileHandle != SYS_FS_HANDLE_INVALID) {
                SYS_CONSOLE_PRINT("FS:File \"mnt/mchpSite1/index.htm\" open succeeded\r\n");
            } else {
                SYS_CONSOLE_PRINT("FS:File \"mnt/mchpSite1/index.htm\" open failed\r\n");
            }
            SYS_FS_FileClose(fileHandle);
            
            msd_appData.state = MSD_APP_STATE_CHECK_SWITCH;     
            break;

        case MSD_APP_STATE_CHECK_SWITCH:
            if (SWITCH1_Get() == SWITCH1_STATE_PRESSED) {
                msd_appData.state = MSD_APP_STATE_CLEAR_DRIVE;
            } else {
                msd_appData.state = MSD_APP_STATE_SERVICE_TASKS;
            }
            break;

        case MSD_APP_STATE_CLEAR_DRIVE:
            opt.fmt = SYS_FS_FORMAT_FAT;
            opt.au_size = 0;
            SYS_CONSOLE_PRINT("Start Format\r\n");
            if (SYS_FS_DriveFormat(SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0, &opt, (void *) work, SYS_FS_FAT_MAX_SS) != SYS_FS_RES_SUCCESS) {
                /* Format of the disk failed. */
                SYS_CONSOLE_PRINT("Media Format failed\r\n");
                msd_appData.state = MSD_APP_STATE_ERROR;
            } else {
                SYS_FS_DriveLabelSet(SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0, "CUROSITY");
            }
            msd_appData.state = MSD_APP_STATE_SERVICE_TASKS;
            break;

        case MSD_APP_STATE_ERROR:
            break;


        case MSD_APP_CONNECT_USB:
            msd_appData.usbDeviceHandle = USB_DEVICE_Open(USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE);
            if (msd_appData.usbDeviceHandle != USB_DEVICE_HANDLE_INVALID) {
                /* Set the Event Handler. We will start receiving events after
                 * the handler is set */
                USB_DEVICE_EventHandlerSet(msd_appData.usbDeviceHandle, APP_USBDeviceEventHandler, (uintptr_t) & msd_appData);
                SYS_CONSOLE_PRINT("MSD Handle valid\r\n");
                msd_appData.state = MSD_APP_STATE_SERVICE_TASKS;
                break;
            } else {
                SYS_CONSOLE_PRINT("Retrying USB Device Open\r\n");
                msd_appData.state = MSD_APP_STATE_ERROR;
                break;
            }

        case MSD_APP_STATE_SERVICE_TASKS:
        {            
            if(mqtt_init_flag == true){
                APP_MQTT_Tasks();
            }

            {
                static SYS_MQTT_STATUS status = -1;
                extern SYS_MODULE_OBJ g_sSysMqttHandle;
                SYS_MQTT_STATUS current = SYS_MQTT_GetStatus(g_sSysMqttHandle);
                if (status != current) {
                    switch (current) {
                        case SYS_MQTT_STATUS_IDLE: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_IDLE\r\n");
                            break;
                        case SYS_MQTT_STATUS_LOWER_LAYER_DOWN: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_LOWER_LAYER_DOWN\r\n");
                            break;
                        case SYS_MQTT_STATUS_SOCK_CLIENT_CONNECTING: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_SOCK_CLIENT_CONNECTING\r\n");
                            break;
                        case SYS_MQTT_STATUS_SOCK_CONNECTED: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_SOCK_CONNECTED\r\n");
                            break;
                        case SYS_MQTT_STATUS_SOCK_OPEN_FAILED: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_SOCK_OPEN_FAILED\r\n");
                            break;
                        case SYS_MQTT_STATUS_MQTT_CONNECTED: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_MQTT_CONNECTED\r\n");
                            break;
                        case SYS_MQTT_STATUS_MQTT_DISCONNECTING: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_MQTT_DISCONNECTING\r\n");
                            break;
                        case SYS_MQTT_STATUS_WAIT_FOR_MQTT_CONACK: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_WAIT_FOR_MQTT_CONACK\r\n");
                            break;
                        case SYS_MQTT_STATUS_WAIT_FOR_MQTT_SUBACK: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_WAIT_FOR_MQTT_SUBACK\r\n");
                            break;
                        case SYS_MQTT_STATUS_WAIT_FOR_MQTT_PUBACK: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_WAIT_FOR_MQTT_PUBACK\r\n");
                            break;
                        case SYS_MQTT_STATUS_WAIT_FOR_MQTT_UNSUBACK: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS_WAIT_FOR_MQTT_UNSUBACK\r\n");
                            break;
                        default: SYS_CONSOLE_PRINT("SYS_MQTT_STATUS Unknown\r\n");
                            break;
                    }
                }
                status = current;
            }            

            break;
        }

            /* TODO: implement your application state machine.*/


            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
