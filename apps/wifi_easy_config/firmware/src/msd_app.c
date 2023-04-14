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

extern EXCEPT_MSG last_expt_msg;
extern SYS_MODULE_OBJ g_sSysMqttHandle;
                
volatile bool print_delay_started = false;
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define CMD_MSG(x) (*pCmdIO->pCmdApi->msg)(cmdIoParam, x) 
#define CMD_PRINTF (*pCmdIO->pCmdApi->print)  // CMD_PRINTF(cmdIoParam, "%d", c );

static void my_pub(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc == 2) {
        APP_MQTT_PublishMsg(argv[1]);
        CMD_PRINTF(cmdIoParam, "Publish MQTT Message: %s\n\r",argv[1]);
    }
    else
    {
        CMD_PRINTF(cmdIoParam, "Wrong Parameter Number\r\n");
    }
}

static void my_connect(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc == 1) {
        CMD_PRINTF(cmdIoParam, "Connect to Default MQTT Broker: %s \n\r",SYS_MQTT_INDEX0_BROKER_NAME);
        APP_MQTT_Initialize();
        mqtt_init_flag = true;
    } else if (argc == 2) {
        strcpy((char*)g_sSysMqttConfig.sBrokerConfig.brokerName, argv[1]);
        CMD_PRINTF(cmdIoParam, "Connect to MQTT Broker: %s\n\r",argv[1]);
        APP_MQTT_Initialize();
        mqtt_init_flag = true;
    } else if (argc == 3) {
        strcpy((char*)g_sSysMqttConfig.sBrokerConfig.brokerName, argv[1]);
        strcpy((char*)g_sSysMqttConfig.sSubscribeConfig[0].topicName, argv[2]);
        CMD_PRINTF(cmdIoParam, "Connect to MQTT Broker: %s with topic: %s\n\r",argv[1],argv[2]);
        APP_MQTT_Initialize();
        mqtt_init_flag = true;
    } else if (argc == 4) {
        strcpy((char*)g_sSysMqttConfig.sBrokerConfig.brokerName, argv[1]);
        strcpy((char*) g_sSysMqttConfig.sSubscribeConfig[0].topicName, argv[2]);
        if (strcmp(argv[3], "1") == 0) {
            g_sSysMqttConfig.sBrokerConfig.tlsEnabled = 1;
            g_sSysMqttConfig.sBrokerConfig.serverPort = 8883;
        }                
        CMD_PRINTF(cmdIoParam, "Connect to MQTT Broker: %s with topic: %s tls =%s\n\r",argv[1],argv[2],argv[3]);
        APP_MQTT_Initialize();
        mqtt_init_flag = true;
    } else {
        CMD_MSG("Wrong Parameter Number\r\n");
    }
}

static void my_sub(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    SYS_MQTT_SubscribeConfig subConfig;
    subConfig.qos = 0;
    
    CMD_PRINTF(cmdIoParam, "%s\n\r",argv[1]);
    strcpy(subConfig.topicName, argv[1]);
    SYS_MQTT_Subscribe(g_sSysMqttHandle, &subConfig);
}

static void my_diconnect(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    
    APP_MQTT_Disconnect();
    CMD_PRINTF(cmdIoParam, "Disconnect from MQTT Broker\n\r");
}

static void CommandHeap(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    HeapStats_t xHeapStats;
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    (*pCmdIO->pCmdApi->msg)(cmdIoParam, "\n\rHeap Statistics\r\n");

    vPortGetHeapStats(&xHeapStats);
    
    CMD_PRINTF(cmdIoParam, "configTOTAL_HEAP_SIZE           : %d\r\n", configTOTAL_HEAP_SIZE);        
    CMD_PRINTF(cmdIoParam, "xAvailableHeapSpaceInBytes      : %d\r\n", xHeapStats.xAvailableHeapSpaceInBytes);
    CMD_PRINTF(cmdIoParam, "xSizeOfLargestFreeBlockInBytes  : %d\r\n", xHeapStats.xSizeOfLargestFreeBlockInBytes);
    CMD_PRINTF(cmdIoParam, "xSizeOfSmallestFreeBlockInBytes : %d\r\n", xHeapStats.xSizeOfSmallestFreeBlockInBytes);
    CMD_PRINTF(cmdIoParam, "xNumberOfFreeBlocks             : %d\r\n", xHeapStats.xNumberOfFreeBlocks);
    CMD_PRINTF(cmdIoParam, "xMinimumEverFreeBytesRemaining  : %d\r\n", xHeapStats.xMinimumEverFreeBytesRemaining);
    CMD_PRINTF(cmdIoParam, "xNumberOfSuccessfulAllocations  : %d\r\n", xHeapStats.xNumberOfSuccessfulAllocations);
    CMD_PRINTF(cmdIoParam, "xNumberOfSuccessfulFrees        : %d\r\n", xHeapStats.xNumberOfSuccessfulFrees);
//    (*pCmdIO->pCmdApi->print)(cmdIoParam, "xNumberOfFaileddAllocations     : %d\r\n", xHeapStats.xNumberOfFaileddAllocations);
}

static void my_dump(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    uint32_t addr;
    uint32_t count;
    uint32_t ix, jx;
    uint8_t *puc;
    char str[64];
    int flag = 0;

    addr = strtoul(argv[1], NULL, 16);
    count = strtoul(argv[2], NULL, 16);
    puc = (uint8_t *) addr;
    puc = (uint8_t *) addr;

    jx = 0;
    for (ix = 0; ix < count; ix++) {
        if ((ix % 16) == 0) {
            if(flag == 1){
                str[16] = 0;
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "   %s", str);
            }
            (*pCmdIO->pCmdApi->print)(cmdIoParam, "\n\r%08x: ", puc);
            flag = 1;
            jx = 0;
        }
        (*pCmdIO->pCmdApi->print)(cmdIoParam, " %02x", *puc);
        if ( (*puc > 31) && (*puc < 127) )
            str[jx++] = *puc;
        else
            str[jx++] = '.';
        puc++;
    }
    str[jx] = 0;
    (*pCmdIO->pCmdApi->print)(cmdIoParam, "   %s", str);
    (*pCmdIO->pCmdApi->print)(cmdIoParam, "\n\rReady\n\r");
    
}

static void my_log(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv) {
    const void* cmdIoParam = pCmdIO->cmdIoParam;    
    uint32_t ix;
    char str[128];    
    int cc;
    cc = LOG_GetLogSize();

    (*pCmdIO->pCmdApi->print)(cmdIoParam, "Log Size:%d\n\r",cc);
    for(ix=0;ix<cc;ix++){
        LOG_GetData(ix,str);
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "%s\n\r",str);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }    
}

const SYS_CMD_DESCRIPTOR msd_cmd_tbl[] = {
    {"pub", (SYS_CMD_FNC) my_pub, ": Publish MQTT Message: pub msg "},
    {"sub", (SYS_CMD_FNC) my_sub, ": Subcribe MQTT Message: sub topic "},    
    {"con", (SYS_CMD_FNC) my_connect, ": Connect to MQTT Broker: con [host] [topic] [tls enabled]"},
    {"dis", (SYS_CMD_FNC) my_diconnect, ": Disconnect from MQTT Broker "},
    {"heap",(SYS_CMD_FNC) CommandHeap, ": heap statistics"},    
    {"log", (SYS_CMD_FNC) my_log, ": print log data"}, 
    {"dump",(SYS_CMD_FNC) my_dump,    ": dump memory"},   
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
            SYS_WSS_RESULT result;
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            print_delay_started = true;
            if (last_expt_msg.magic == MAGIC_CODE) {
                SYS_CONSOLE_PRINT("\n\r!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
                SYS_CONSOLE_PRINT("Last Runtime has ended with the following Message:\n\r");
                {
                    char ch;
                    int ix = 0;
                    for (ix = 0; ix < 4096; ix++) {
                        ch = last_expt_msg.msg[ix];
                        if (ch == 0)break;
                        SYS_CONSOLE_PRINT("%c", ch);
                    }
                }
                SYS_CONSOLE_PRINT("%c", last_expt_msg.msg[0]);
                SYS_CONSOLE_PRINT("\n\r!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
                last_expt_msg.magic = 0;
            }

            result = SYS_WSS_register_callback(wss_user_callback, 0);
            if (SYS_WSS_SUCCESS == result) {
                SYS_CONSOLE_PRINT("Registered call back with WSS service successfully\r\n");
            }

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
            
            do {                
                if (SYS_FS_DirRead(dirHandle, &stat) == SYS_FS_RES_FAILURE) {
                    SYS_CONSOLE_PRINT("FS:Directory read failed\r\n");
                } else {
                    if(stat.fname[0] == '\0') break;
                    SYS_CONSOLE_PRINT("FS:%s\n\r", stat.fname);             
                }                
            } while (1);
                   
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

#include "config/pic32mz_w1_curiosity_freertos/system/wifiprov/sys_wifiprov_json.h"
volatile uint8_t wssSocketIndex = 0;
uint16_t Temperature = 25;
bool ParseData(uint8_t buffer[], int length) {
    struct json_obj root, child; //, sub;
    bool error = false;

    SYS_CONSOLE_PRINT("JSON: Parse Data\n\r");
    if (buffer) {
        SYS_CONSOLE_PRINT("JSON: buffer is valid: %d \n\r", length);
        buffer[length] = 0;
        SYS_CONSOLE_PRINT("JSON: %s\n\r", buffer);

        /* Creating JSON object to parse incoming JSON data */
        if (!json_create(&root, (const char*) buffer, length)) {
            
            SYS_CONSOLE_PRINT("JSON: Start\n\r");
            if (!json_find(&root, "var1", &child)) {
                SYS_CONSOLE_PRINT("JSON: Found var1: %s type:%d\n\r", child.value.s,child.type);                
            }
            
            if (!json_find(&root, "var2", &child)) {
                SYS_CONSOLE_PRINT("JSON: Found var2: %s type:%d\n\r", child.value.s,child.type);     
            } 

            if (!json_find(&root, "var3", &child)) {
                SYS_CONSOLE_PRINT("JSON: Found var3: %d type:%d\n\r", child.value.i,child.type);
            } 

             if (!json_find(&root, "Control", &child)) {
                SYS_CONSOLE_PRINT("JSON: Found Control: %s type:%d\n\r", child.value.s,child.type);
                char str[50];
                sprintf(str,"{\"Temperature\":%d}",Temperature);
                SYS_WSS_sendMessage(1, SYS_WSS_FRAME_TEXT,(uint8_t*)str,strlen(str), wssSocketIndex);
            } 
            //            if (!json_find(&root, "variable_set", &child)) {
            //                child.value.b;
            //            }
            //            else {
            //                error = true;
            //            }

            //            /* Verifying JSON  "save_config" field */
            //            if (!json_find(&root, "save_config", &child)) {
            //                child.value.b;
            //            }
            //            else {
            //                error = true;
            //            }
            //
            //            /* Verifying JSON  "countrycode" field */
            //            if (!json_find(&root, "countrycode", &child)) {
            //                char buff[20];
            //                memcpy(buff, child.value.s, strlen(child.value.s));
            //            }
            //            else {
            //                error = true;
            //            }
            //                if (!json_find(&child, "auto", &sub)) {
            //                    sub.value.b;
            //                }
            //                else {
            //                    error = true;
            //                }
            //
            //                if (!json_find(&child, "auth", &sub)) {
            //                    sub.value.i;
            //                } else {
            //                    error = true;
            //                }
            //
            //                if (!json_find(&child, "SSID", &sub)) {
            //
            //                    
            //
            //                    if (!json_find(&child, "PWD", &sub)) {
            //                        char buff[20];
            //                        memcpy(buff, child.value.s, strlen(child.value.s));
            //                    }
            //                    else {
            //                        error = true;
            //                    }
            //                }
            //                /* Verifying JSON  "AP" field */
            //                if (!json_find(&root, "AP", &child)) {
            //                    if (!json_find(&child, "ch", &sub)) {
            //                        sub.value.i;
            //                    } else {
            //                        error = true;
            //                    }
            //
            //                    if (!json_find(&child, "ssidv", &sub)) {
            //                        sub.value.b;
            //                    } else {
            //                        error = true;
            //                    }
            //
            //                    if (!json_find(&child, "auth", &sub)) {
            //                        sub.value.i;
            //                    } else {
            //                        error = true;
            //                    }
            //
            //                    if (!json_find(&child, "SSID", &sub)) {
            //                        char buff[20];
            //                        memcpy(buff, child.value.s, strlen(child.value.s));
            //                    }
            //                    else {
            //                        error = true;
            //                    }
            //
            //                    if (!json_find(&child, "PWD", &sub)) {
            //                        char buff[20];
            //                        memcpy(buff, child.value.s, strlen(child.value.s));
            //                    }
            //                    else {
            //                        error = true;
            //                    }
            //                }
            //            }
        }
    }
    return error;
}

void* APP_Calloc(size_t nElems, size_t elemSize) {
    size_t nBytes = nElems * elemSize;

    void* ptr = pvPortMalloc(nBytes);
    if (ptr) {
        memset(ptr, 0, nBytes);
    }

    return ptr;
}

void * malloc(size_t size){
    return pvPortMalloc(size);
}

void free(void *ptr){
    vPortFree(ptr);
}

/*******************************************************************************
 End of File
 */
