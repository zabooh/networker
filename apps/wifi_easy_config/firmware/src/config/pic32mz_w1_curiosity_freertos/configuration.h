/*******************************************************************************
  System Configuration Header

  File Name:
    configuration.h

  Summary:
    Build-time configuration header for the system defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "user.h"
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Configuration
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
/* TIME System Service Configuration Options */
#define SYS_TIME_INDEX_0                            (0)
#define SYS_TIME_MAX_TIMERS                         (5)
#define SYS_TIME_HW_COUNTER_WIDTH                   (32)
#define SYS_TIME_HW_COUNTER_PERIOD                  (4294967295U)
#define SYS_TIME_HW_COUNTER_HALF_PERIOD             (SYS_TIME_HW_COUNTER_PERIOD>>1)
#define SYS_TIME_CPU_CLOCK_FREQUENCY                (200000000)
#define SYS_TIME_COMPARE_UPDATE_EXECUTION_CYCLES    (620)

#define SYS_CONSOLE_INDEX_0                       0

/* RX buffer size has one additional element for the empty spot needed in circular buffer */
#define SYS_CONSOLE_USB_CDC_RD_BUFFER_SIZE_IDX0    129

/* TX buffer size has one additional element for the empty spot needed in circular buffer */
#define SYS_CONSOLE_USB_CDC_WR_BUFFER_SIZE_IDX0    512
    
/* Console Driver Instance 0 RTOS Configurations*/
#define SYS_CONSOLE_RTOS_STACK_SIZE_IDX0               256
#define SYS_CONSOLE_RTOS_TASK_PRIORITY_IDX0                     1

/*** WSS Configuration ***/
#define SYS_WSS_RTOS_STACK_SIZE     2048
#define SYS_WSS_RTOS_TASK_PRIORITY  1
#define SYS_WSS_RTOS_TASK_DELAY     1

#define SYS_WSS_PORT                        8000
#define SYS_WSS_ENABLE_TLS   			    false
#define SYS_WSS_ENABLE_DEBUG   			    0
#define SYS_WSS_MAX_RX_BUFFER               1400
#define SYS_WSS_MAX_NUM_CLIENTS             2
#define SYS_WSS_START_AT_BOOT   			1
#define SYS_WSS_CLIENT_TIMEOUT              30000

#define WOLFSSL_BASE64_ENCODE

/* File System Service Configuration */

#define SYS_FS_MEDIA_NUMBER               1
#define SYS_FS_VOLUME_NUMBER              1

#define SYS_FS_AUTOMOUNT_ENABLE           false
#define SYS_FS_MAX_FILES                  10
#define SYS_FS_MAX_FILE_SYSTEM_TYPE       1
#define SYS_FS_MEDIA_MAX_BLOCK_SIZE       512
#define SYS_FS_MEDIA_MANAGER_BUFFER_SIZE  2048
#define SYS_FS_USE_LFN                    1
#define SYS_FS_FILE_NAME_LEN              255
#define SYS_FS_CWD_STRING_LEN             1024

/* File System RTOS Configurations*/
#define SYS_FS_STACK_SIZE                 1024
#define SYS_FS_PRIORITY                   1

#define SYS_FS_FAT_VERSION                "v0.14b"
#define SYS_FS_FAT_READONLY               false
#define SYS_FS_FAT_CODE_PAGE              437
#define SYS_FS_FAT_MAX_SS                 SYS_FS_MEDIA_MAX_BLOCK_SIZE
#define SYS_FS_FAT_ALIGNED_BUFFER_LEN     512






#define SYS_NET_SUPP_INTF_WIFI_ETHERNET
#define SYS_NET_SUPP_NUM_OF_SOCKS        		3

#define SYS_NET_INDEX0_INTF       				SYS_NET_INTF_WIFI
#define SYS_NET_INDEX0_MODE       				SYS_NET_MODE_SERVER
#define SYS_NET_INDEX0_PORT        				8000
#define SYS_NET_INDEX0_RECONNECT       			1
#define SYS_NET_INDEX0_ENABLE_TLS        		1
#define SYS_NET_INDEX0_IPPROT       			SYS_NET_IP_PROT_TCP
#define SYS_NET_INDEX0_HOST_NAME        		"192.168.1.1"


#define SYS_NET_VALID_INST1
#define SYS_NET_INDEX1_INTF       				SYS_NET_INTF_ETHERNET
#define SYS_NET_INDEX1_MODE       				SYS_NET_MODE_CLIENT
#define SYS_NET_INDEX1_PORT        				1
#define SYS_NET_INDEX1_RECONNECT       			1
#define SYS_NET_INDEX1_ENABLE_TLS        		0
#define SYS_NET_INDEX1_IPPROT       			SYS_NET_IP_PROT_TCP
#define SYS_NET_INDEX1_HOST_NAME        		"192.168.1.1"

#define SYS_NET_TLS_ENABLED
#define WOLFSSL_TLS13_NO_PEEK_HANDSHAKE_DONE


#define SYS_NET_CLICMD_ENABLED



#define SYS_MQTT_PAHO

#define SYS_MQTT_INDEX0_MQTT_PORT        				8883
#define SYS_MQTT_INDEX0_BROKER_NAME        				"test.mosquitto.org"
#define SYS_MQTT_INDEX0_ENABLE_TLS        				true
#define SYS_MQTT_INDEX0_RECONNECT        				true
#define SYS_MQTT_INDEX0_CLEAN_SESSION					true
#define SYS_MQTT_INDEX0_CLIENT_ID        				""
#define SYS_MQTT_INDEX0_KEEPALIVE_INTERVAL 				60
#define SYS_MQTT_INDEX0_MQTT_INTF        				SYS_MQTT_INTF_WIFI

#define SYS_MQTT_INDEX0_SUB_TOPIC_COUNT					0
#define SYS_MQTT_INDEX0_TOPIC_NAME        				" "
#define SYS_MQTT_INDEX0_SUB_QOS							0
#define SYS_MQTT_INDEX0_ENTRY_VALID        				false

#define SYS_MQTT_CLICMD_ENABLED




#define SYS_MQTT_CFG_LWT_ENABLE								false


#define SYS_CMD_ENABLE
#define SYS_CMD_DEVICE_MAX_INSTANCES       SYS_CONSOLE_DEVICE_MAX_INSTANCES
#define SYS_CMD_PRINT_BUFFER_SIZE          1024
#define SYS_CMD_BUFFER_DMA_READY

/* Command System Service RTOS Configurations*/
#define SYS_CMD_RTOS_STACK_SIZE                1024
#define SYS_CMD_RTOS_TASK_PRIORITY             1


#define SYS_DEBUG_ENABLE
#define SYS_DEBUG_GLOBAL_ERROR_LEVEL       SYS_ERROR_DEBUG
#define SYS_DEBUG_BUFFER_DMA_READY
#define SYS_DEBUG_USE_CONSOLE


#define SYS_CONSOLE_DEVICE_MAX_INSTANCES   			1
#define SYS_CONSOLE_UART_MAX_INSTANCES 	   			1
#define SYS_CONSOLE_USB_CDC_MAX_INSTANCES 	   		1
#define SYS_CONSOLE_PRINT_BUFFER_SIZE        		256

#define SYS_CONSOLE_USB_CDC_READ_WRITE_BUFFER_SIZE 	64



// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
/* Memory Driver Global Configuration Options */
#define DRV_MEMORY_INSTANCES_NUMBER          1


/*** MIIM Driver Configuration ***/
#define DRV_MIIM_ETH_MODULE_ID              _ETH_BASE_ADDRESS
#define DRV_MIIM_INSTANCES_NUMBER           1
#define DRV_MIIM_INSTANCE_OPERATIONS        4
#define DRV_MIIM_INSTANCE_CLIENTS           2
#define DRV_MIIM_CLIENT_OP_PROTECTION   false
#define DRV_MIIM_COMMANDS   false
#define DRV_MIIM_DRIVER_OBJECT              DRV_MIIM_OBJECT_BASE_Default
#define DRV_MIIM_DRIVER_INDEX               DRV_MIIM_INDEX_0              

/* MIIM RTOS Configurations*/
#define DRV_MIIM_RTOS_STACK_SIZE                1024
#define DRV_MIIM_RTOS_TASK_PRIORITY             1



/* Memory Driver Instance 0 Configuration */
#define DRV_MEMORY_INDEX_0                   0
#define DRV_MEMORY_CLIENTS_NUMBER_IDX0       2
#define DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX0    1

/* Memory Driver Instance 0 RTOS Configurations*/
#define DRV_MEMORY_STACK_SIZE_IDX0           1024
#define DRV_MEMORY_PRIORITY_IDX0             1
#define DRV_MEMORY_RTOS_DELAY_IDX0                         3

/* SST26 Driver Instance Configuration */
#define DRV_SST26_INDEX                 0
#define DRV_SST26_CLIENTS_NUMBER        1
#define DRV_SST26_START_ADDRESS         0x0
#define DRV_SST26_PAGE_SIZE             256
#define DRV_SST26_ERASE_BUFFER_SIZE     4096
#define DRV_SST26_CHIP_SELECT_PIN       SYS_PORT_PIN_RA1

/*** WiFi PIC32MZW1 Driver Configuration ***/
#define WDRV_PIC32MZW1_DEVICE_USE_SYS_DEBUG
#define WDRV_PIC32MZW_WPA3_PERSONAL_SUPPORT
#define WDRV_PIC32MZW_BA414E_SUPPORT
#define WDRV_PIC32MZW_BIGINTSW_SUPPORT
#define WDRV_PIC32MZW_ALARM_PERIOD_1MS          390
#define WDRV_PIC32MZW_ALARM_PERIOD_MAX          168


// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

/*** ICMPv4 Server Configuration ***/
#define TCPIP_STACK_USE_ICMP_SERVER
#define TCPIP_ICMP_ECHO_ALLOW_BROADCASTS    false

/*** ICMPv4 Client Configuration ***/
#define TCPIP_STACK_USE_ICMP_CLIENT
#define TCPIP_ICMP_ECHO_REQUEST_TIMEOUT        500
#define TCPIP_ICMP_TASK_TICK_RATE              33
#define TCPIP_STACK_MAX_CLIENT_ECHO_REQUESTS   4
#define TCPIP_ICMP_COMMAND_ENABLE              true
#define TCPIP_STACK_COMMANDS_ICMP_ECHO_REQUESTS         4
#define TCPIP_STACK_COMMANDS_ICMP_ECHO_REQUEST_DELAY    1000
#define TCPIP_STACK_COMMANDS_ICMP_ECHO_TIMEOUT          5000
#define TCPIP_STACK_COMMANDS_ICMP_ECHO_REQUEST_BUFF_SIZE    2000
#define TCPIP_STACK_COMMANDS_ICMP_ECHO_REQUEST_DATA_SIZE    100

/******************************************************************************/
/*wolfSSL TLS Layer Configuration*/
/******************************************************************************/

#define WOLFSSL_ALT_NAMES
#define WOLFSSL_DER_LOAD
#define KEEP_OUR_CERT
#define KEEP_PEER_CERT
#define HAVE_CRL_IO
#define HAVE_IO_TIMEOUT
#define TFM_NO_ASM
#define WOLFSSL_NO_ASM
#define SIZEOF_LONG_LONG 8
#define WOLFSSL_USER_IO
#define NO_WRITEV
#define MICROCHIP_TCPIP
#define HAVE_FFDHE_2048
#define NO_PWDBASED
#define HAVE_TLS_EXTENSIONS
#define WOLFSSL_TLS13
#define HAVE_SUPPORTED_CURVES
#define WOLFSSL_SMALL_STACK
#define NO_OLD_TLS
#define USE_FAST_MATH


/*** TCP Configuration ***/
#define TCPIP_TCP_MAX_SEG_SIZE_TX		        	1460
#define TCPIP_TCP_SOCKET_DEFAULT_TX_SIZE			512
#define TCPIP_TCP_SOCKET_DEFAULT_RX_SIZE			512
#define TCPIP_TCP_DYNAMIC_OPTIONS             			true
#define TCPIP_TCP_START_TIMEOUT_VAL		        	1000
#define TCPIP_TCP_DELAYED_ACK_TIMEOUT		    		100
#define TCPIP_TCP_FIN_WAIT_2_TIMEOUT		    		5000
#define TCPIP_TCP_KEEP_ALIVE_TIMEOUT		    		10000
#define TCPIP_TCP_CLOSE_WAIT_TIMEOUT		    		0
#define TCPIP_TCP_MAX_RETRIES		            		5
#define TCPIP_TCP_MAX_UNACKED_KEEP_ALIVES			6
#define TCPIP_TCP_MAX_SYN_RETRIES		        	3
#define TCPIP_TCP_AUTO_TRANSMIT_TIMEOUT_VAL			40
#define TCPIP_TCP_WINDOW_UPDATE_TIMEOUT_VAL			200
#define TCPIP_TCP_MAX_SOCKETS		                10
#define TCPIP_TCP_TASK_TICK_RATE		        	1
#define TCPIP_TCP_MSL_TIMEOUT		        	    0
#define TCPIP_TCP_QUIET_TIME		        	    0
#define TCPIP_TCP_COMMANDS   false
#define TCPIP_TCP_EXTERN_PACKET_PROCESS   false
#define TCPIP_TCP_DISABLE_CRYPTO_USAGE		        	    false



/*** ARP Configuration ***/
#define TCPIP_ARP_CACHE_ENTRIES                 		5
#define TCPIP_ARP_CACHE_DELETE_OLD		        	true
#define TCPIP_ARP_CACHE_SOLVED_ENTRY_TMO			1200
#define TCPIP_ARP_CACHE_PENDING_ENTRY_TMO			60
#define TCPIP_ARP_CACHE_PENDING_RETRY_TMO			2
#define TCPIP_ARP_CACHE_PERMANENT_QUOTA		    		50
#define TCPIP_ARP_CACHE_PURGE_THRESHOLD		    		75
#define TCPIP_ARP_CACHE_PURGE_QUANTA		    		1
#define TCPIP_ARP_CACHE_ENTRY_RETRIES		    		3
#define TCPIP_ARP_GRATUITOUS_PROBE_COUNT			1
#define TCPIP_ARP_TASK_PROCESS_RATE		        	2000
#define TCPIP_ARP_PRIMARY_CACHE_ONLY		        	true
#define TCPIP_ARP_COMMANDS false



/* Network Configuration Index 0 */
#define TCPIP_NETWORK_DEFAULT_INTERFACE_NAME_IDX0	"PIC32MZW1"
#define TCPIP_IF_PIC32MZW1

#define TCPIP_NETWORK_DEFAULT_HOST_NAME_IDX0				"MCHPBOARD_W"
#define TCPIP_NETWORK_DEFAULT_MAC_ADDR_IDX0				0

#define TCPIP_NETWORK_DEFAULT_IP_ADDRESS_IDX0			"0.0.0.0"
#define TCPIP_NETWORK_DEFAULT_IP_MASK_IDX0			"255.255.255.0"
#define TCPIP_NETWORK_DEFAULT_GATEWAY_IDX0			"192.168.1.1"
#define TCPIP_NETWORK_DEFAULT_DNS_IDX0				"192.168.1.1"
#define TCPIP_NETWORK_DEFAULT_SECOND_DNS_IDX0			"0.0.0.0"
#define TCPIP_NETWORK_DEFAULT_POWER_MODE_IDX0			"full"
#define TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS_IDX0			\
													TCPIP_NETWORK_CONFIG_DHCP_CLIENT_ON |\
													TCPIP_NETWORK_CONFIG_DNS_CLIENT_ON |\
													TCPIP_NETWORK_CONFIG_IP_STATIC
													
#define TCPIP_NETWORK_DEFAULT_MAC_DRIVER_IDX0			WDRV_PIC32MZW1_MACObject



/* Network Configuration Index 1 */
#define TCPIP_NETWORK_DEFAULT_INTERFACE_NAME_IDX1	"ETHMAC"
#define TCPIP_IF_PIC32MZW_ETHMAC	

#define TCPIP_NETWORK_DEFAULT_HOST_NAME_IDX1				"MCHPBOARD_E"
#define TCPIP_NETWORK_DEFAULT_MAC_ADDR_IDX1				0

#define TCPIP_NETWORK_DEFAULT_IP_ADDRESS_IDX1			"192.168.100.10"
#define TCPIP_NETWORK_DEFAULT_IP_MASK_IDX1			"255.255.255.0"
#define TCPIP_NETWORK_DEFAULT_GATEWAY_IDX1			"192.168.100.1"
#define TCPIP_NETWORK_DEFAULT_DNS_IDX1				"192.168.100.1"
#define TCPIP_NETWORK_DEFAULT_SECOND_DNS_IDX1			"0.0.0.0"
#define TCPIP_NETWORK_DEFAULT_POWER_MODE_IDX1			"full"
#define TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS_IDX1			\
													TCPIP_NETWORK_CONFIG_DHCP_CLIENT_ON |\
													TCPIP_NETWORK_CONFIG_DNS_CLIENT_ON |\
													TCPIP_NETWORK_CONFIG_IP_STATIC
													
#define TCPIP_NETWORK_DEFAULT_MAC_DRIVER_IDX1			DRV_ETHMAC_PIC32MACObject



/*** telnet Configuration ***/
#define TCPIP_STACK_USE_TELNET_SERVER
#define TCPIP_TELNET_MAX_CONNECTIONS    2
#define TCPIP_TELNET_TASK_TICK_RATE     100
#define TCPIP_TELNET_SKT_TX_BUFF_SIZE   0
#define TCPIP_TELNET_SKT_RX_BUFF_SIZE   0
#define TCPIP_TELNET_LISTEN_PORT        23
#define TCPIP_TELNET_PRINT_BUFF_SIZE    200
#define TCPIP_TELNET_LINE_BUFF_SIZE     80
#define TCPIP_TELNET_USERNAME_SIZE      15
#define TCPIP_TELNET_CONFIG_FLAGS       \
                                       TCPIP_TELNET_FLAG_NONE

#define TCPIP_TELNET_OBSOLETE_AUTHENTICATION false
#define TCPIP_TELNET_AUTHENTICATION_CONN_INFO true



/*** IPv4 Configuration ***/
#define TCPIP_IPV4_ARP_SLOTS                        10
#define TCPIP_IPV4_EXTERN_PACKET_PROCESS   false

#define TCPIP_IPV4_COMMANDS false

#define TCPIP_IPV4_FORWARDING_ENABLE    false 





/*** UDP Configuration ***/
#define TCPIP_UDP_MAX_SOCKETS		                	10
#define TCPIP_UDP_SOCKET_DEFAULT_TX_SIZE		    	512
#define TCPIP_UDP_SOCKET_DEFAULT_TX_QUEUE_LIMIT    	 	3
#define TCPIP_UDP_SOCKET_DEFAULT_RX_QUEUE_LIMIT			3
#define TCPIP_UDP_USE_POOL_BUFFERS   false
#define TCPIP_UDP_USE_TX_CHECKSUM             			true
#define TCPIP_UDP_USE_RX_CHECKSUM             			true
#define TCPIP_UDP_COMMANDS   false
#define TCPIP_UDP_EXTERN_PACKET_PROCESS   false


                                                  
#define TCPIP_INTMAC_PHY_CONFIG_FLAGS              	( 0 \
                                                    | DRV_ETHPHY_CFG_AUTO \
                                                    )

#define TCPIP_INTMAC_PHY_LINK_INIT_DELAY  			500
#define TCPIP_INTMAC_PHY_ADDRESS		    			0
#define DRV_ETHPHY_INSTANCES_NUMBER					1
#define DRV_ETHPHY_CLIENTS_NUMBER					1
#define DRV_ETHPHY_INDEX		        			1
#define DRV_ETHPHY_PERIPHERAL_ID					1
#define DRV_ETHPHY_NEG_INIT_TMO		    			1
#define DRV_ETHPHY_NEG_DONE_TMO		    			2000
#define DRV_ETHPHY_RESET_CLR_TMO					500


/* MPLAB Harmony Net Presentation Layer Definitions*/
#define NET_PRES_NUM_INSTANCE 1
#define NET_PRES_NUM_SOCKETS 10

/* Net Pres RTOS Configurations*/
#define NET_PRES_RTOS_STACK_SIZE                4096
#define NET_PRES_RTOS_TASK_PRIORITY             1
	
#define FREERTOS




/*** DNS Client Configuration ***/
#define TCPIP_STACK_USE_DNS
#define TCPIP_DNS_CLIENT_SERVER_TMO					60
#define TCPIP_DNS_CLIENT_TASK_PROCESS_RATE			200
#define TCPIP_DNS_CLIENT_CACHE_ENTRIES				5
#define TCPIP_DNS_CLIENT_CACHE_ENTRY_TMO			0
#define TCPIP_DNS_CLIENT_CACHE_PER_IPV4_ADDRESS		5
#define TCPIP_DNS_CLIENT_CACHE_PER_IPV6_ADDRESS		1
#define TCPIP_DNS_CLIENT_ADDRESS_TYPE			    IP_ADDRESS_TYPE_IPV4
#define TCPIP_DNS_CLIENT_CACHE_DEFAULT_TTL_VAL		1200
#define TCPIP_DNS_CLIENT_LOOKUP_RETRY_TMO			2
#define TCPIP_DNS_CLIENT_MAX_HOSTNAME_LEN			64
#define TCPIP_DNS_CLIENT_MAX_SELECT_INTERFACES		4
#define TCPIP_DNS_CLIENT_DELETE_OLD_ENTRIES			true
#define TCPIP_DNS_CLIENT_CONSOLE_CMD               	true
#define TCPIP_DNS_CLIENT_USER_NOTIFICATION   false



/* MPLAB Harmony BA414E Driver Definitions*/
#define DRV_BA414E_NUM_CLIENTS 5


/* Net Pres RTOS Configurations*/
#define DRV_BA414E_RTOS_STACK_SIZE           1024
#define DRV_BA414E_RTOS_TASK_PRIORITY             1	


#define SYS_WIFIPROV_NVMADDR        		0x900FF000
#define SYS_WIFIPROV_SAVECONFIG        			true
#define SYS_WIFIPROV_SOCKETPORT        		6666

/* Number of Endpoints used */
#define DRV_USBFS_ENDPOINTS_NUMBER                        5

/* The USB Device Layer will not initialize the USB Driver */
#define USB_DEVICE_DRIVER_INITIALIZE_EXPLICIT

/* Maximum device layer instances */
#define USB_DEVICE_INSTANCES_NUMBER                         1

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE                          64

/* Enable SOF Events */
#define USB_DEVICE_SOF_EVENT_ENABLE


/*** TCPIP MAC Configuration ***/
#define TCPIP_EMAC_TX_DESCRIPTORS				    8
#define TCPIP_EMAC_RX_DESCRIPTORS				    8
#define TCPIP_EMAC_RX_DEDICATED_BUFFERS				4
#define TCPIP_EMAC_RX_INIT_BUFFERS				    0
#define TCPIP_EMAC_RX_LOW_THRESHOLD				    1
#define TCPIP_EMAC_RX_LOW_FILL				        2
#define TCPIP_EMAC_MAX_FRAME		    			1536
#define TCPIP_EMAC_LINK_MTU		    			    1500
#define TCPIP_EMAC_RX_BUFF_SIZE		    			1536
#define TCPIP_EMAC_RX_FRAGMENTS		    			1

#define TCPIP_EMAC_RX_FILTERS                       \
                                                    TCPIP_MAC_RX_FILTER_TYPE_BCAST_ACCEPT |\
                                                    TCPIP_MAC_RX_FILTER_TYPE_MCAST_ACCEPT |\
                                                    TCPIP_MAC_RX_FILTER_TYPE_UCAST_ACCEPT |\
                                                    TCPIP_MAC_RX_FILTER_TYPE_RUNT_REJECT |\
                                                    TCPIP_MAC_RX_FILTER_TYPE_CRC_ERROR_REJECT |\
                                                    0
#define TCPIP_EMAC_ETH_OPEN_FLAGS       			\
                                                    TCPIP_ETH_OPEN_AUTO |\
                                                    TCPIP_ETH_OPEN_FDUPLEX |\
                                                    TCPIP_ETH_OPEN_HDUPLEX |\
                                                    TCPIP_ETH_OPEN_100 |\
                                                    TCPIP_ETH_OPEN_10 |\
                                                    TCPIP_ETH_OPEN_MDIX_AUTO |\
                                                    TCPIP_ETH_OPEN_RMII |\
                                                    0

#define TCPIP_INTMAC_MODULE_ID		    			_ETH_BASE_ADDRESS
#define TCPIP_INTMAC_PERIPHERAL_CLK  				100000000

#define DRV_ETHMAC_INTERRUPT_SOURCE				_ETHERNET_VECTOR

#define DRV_ETHMAC_INTERRUPT_MODE        			true

#define TCPIP_EMAC_AUTO_FLOW_CONTROL_ENABLE        	true
#define TCPIP_EMAC_FLOW_CONTROL_PAUSE_BYTES         3072
#define TCPIP_EMAC_FLOW_CONTROL_FULL_WMARK          2
#define TCPIP_EMAC_FLOW_CONTROL_EMPTY_WMARK         0



/*** DHCP Configuration ***/
#define TCPIP_STACK_USE_DHCP_CLIENT
#define TCPIP_DHCP_TIMEOUT                          10
#define TCPIP_DHCP_TASK_TICK_RATE                   5
#define TCPIP_DHCP_HOST_NAME_SIZE                   20
#define TCPIP_DHCP_CLIENT_CONNECT_PORT              68
#define TCPIP_DHCP_SERVER_LISTEN_PORT               67
#define TCPIP_DHCP_CLIENT_CONSOLE_CMD               true

#define TCPIP_DHCP_USE_OPTION_TIME_SERVER           0
#define TCPIP_DHCP_TIME_SERVER_ADDRESSES            0
#define TCPIP_DHCP_USE_OPTION_NTP_SERVER            0
#define TCPIP_DHCP_NTP_SERVER_ADDRESSES             0
#define TCPIP_DHCP_ARP_LEASE_CHECK_TMO              1000
#define TCPIP_DHCP_WAIT_ARP_FAIL_CHECK_TMO          10



	/*** tcpip_cmd Configuration ***/
	#define TCPIP_STACK_COMMAND_ENABLE


/* Maximum instances of CDC function driver */
#define USB_DEVICE_CDC_INSTANCES_NUMBER                     1


/* CDC Transfer Queue Size for both read and
   write. Applicable to all instances of the
   function driver */
#define USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED                 3


/*** HTTP Configuration ***/
#define TCPIP_STACK_USE_HTTP_SERVER
#define TCPIP_HTTP_MAX_HEADER_LEN		    		15
#define TCPIP_HTTP_CACHE_LEN		        		"600"
#define TCPIP_HTTP_TIMEOUT		            		45
#define TCPIP_HTTP_MAX_CONNECTIONS		    		4
#define TCPIP_HTTP_DEFAULT_FILE		        		"index.htm"
#define TCPIP_HTTP_DEFAULT_LEN		        		10
#define TCPIP_HTTP_MAX_DATA_LEN		        		200
#define TCPIP_HTTP_MIN_CALLBACK_FREE				16
#define TCPIP_HTTP_SKT_TX_BUFF_SIZE		    		0
#define TCPIP_HTTP_SKT_RX_BUFF_SIZE		    		0
#define TCPIP_HTTP_CONFIG_FLAGS		        		1
#define TCPIP_HTTP_WEB_DIR		        		    "/mnt/mchpSite1/"
#define TCPIP_HTTP_USE_POST
#define TCPIP_HTTP_USE_COOKIES
#define TCPIP_HTTP_USE_BASE64_DECODE
#define TCPIP_HTTP_USE_AUTHENTICATION
#define TCPIP_HTTP_TASK_RATE					1
#define TCPIP_HTTP_MALLOC_FUNC                     malloc
#define TCPIP_HTTP_FREE_FUNC                     free

/*** USB Driver Configuration ***/

/* Maximum USB driver instances */
#define DRV_USBFS_INSTANCES_NUMBER                        1

/* Interrupt mode enabled */
#define DRV_USBFS_INTERRUPT_MODE                          true


/* Enables Device Support */
#define DRV_USBFS_DEVICE_SUPPORT                          true
	
/* Disable Host Support */
#define DRV_USBFS_HOST_SUPPORT                            false



/* Alignment for buffers that are submitted to USB Driver*/ 
#define USB_ALIGN  CACHE_ALIGN


/*** DHCP Server Configuration ***/
#define TCPIP_STACK_USE_DHCP_SERVER
#define TCPIP_DHCPS_TASK_PROCESS_RATE                     	200
#define TCPIP_DHCPS_MAX_NUMBER_INSTANCES					1
#define TCPIP_DHCPS_LEASE_ENTRIES_DEFAULT                   15
#define TCPIP_DHCPS_LEASE_SOLVED_ENTRY_TMO                  1200
#define TCPIP_DHCPS_LEASE_REMOVED_BEFORE_ACK                5
#define TCPIP_DHCP_SERVER_DELETE_OLD_ENTRIES              	true
#define TCPIP_DHCPS_LEASE_DURATION	TCPIP_DHCPS_LEASE_SOLVED_ENTRY_TMO

/*** DHCP Server Instance 0 Configuration ***/
#define TCPIP_DHCPS_DEFAULT_IP_ADDRESS_RANGE_START_IDX0             "192.168.1.100"

#define TCPIP_DHCPS_DEFAULT_SERVER_IP_ADDRESS_IDX0                  "192.168.1.1"

#define TCPIP_DHCPS_DEFAULT_SERVER_NETMASK_ADDRESS_IDX0             "255.255.255.0"

#define TCPIP_DHCPS_DEFAULT_SERVER_GATEWAY_ADDRESS_IDX0             "192.168.1.1"

#define TCPIP_DHCPS_DEFAULT_SERVER_PRIMARY_DNS_ADDRESS_IDX0         "192.168.1.1"

#define TCPIP_DHCPS_DEFAULT_SERVER_SECONDARY_DNS_ADDRESS_IDX0       "192.168.1.1"

#define TCPIP_DHCP_SERVER_INTERFACE_INDEX_IDX0                      0

#define TCPIP_DHCP_SERVER_POOL_ENABLED_IDX0                         true

#define TCPIP_DHCP_SERVER_POOL_INDEX_IDX0								0





/*** TCPIP Heap Configuration ***/
#define TCPIP_STACK_USE_EXTERNAL_HEAP

#define TCPIP_STACK_MALLOC_FUNC                     malloc

#define TCPIP_STACK_CALLOC_FUNC                     calloc

#define TCPIP_STACK_FREE_FUNC                       free



#define TCPIP_STACK_HEAP_USE_FLAGS                   TCPIP_STACK_HEAP_FLAG_ALLOC_UNCACHED

#define TCPIP_STACK_HEAP_USAGE_CONFIG                TCPIP_STACK_HEAP_USE_DEFAULT

#define TCPIP_STACK_SUPPORTED_HEAPS                  1




// *****************************************************************************
// *****************************************************************************
// Section: TCPIP Stack Configuration
// *****************************************************************************
// *****************************************************************************

#define TCPIP_STACK_USE_IPV4
#define TCPIP_STACK_USE_TCP
#define TCPIP_STACK_USE_UDP

#define TCPIP_STACK_TICK_RATE		        		1
#define TCPIP_STACK_SECURE_PORT_ENTRIES             10

#define TCPIP_STACK_ALIAS_INTERFACE_SUPPORT   false

#define TCPIP_PACKET_LOG_ENABLE     0

/* TCP/IP stack event notification */
#define TCPIP_STACK_USE_EVENT_NOTIFICATION
#define TCPIP_STACK_USER_NOTIFICATION   true
#define TCPIP_STACK_DOWN_OPERATION   true
#define TCPIP_STACK_IF_UP_DOWN_OPERATION   true
#define TCPIP_STACK_MAC_DOWN_OPERATION  true
#define TCPIP_STACK_INTERFACE_CHANGE_SIGNALING   false
#define TCPIP_STACK_CONFIGURATION_SAVE_RESTORE   true
#define TCPIP_STACK_EXTERN_PACKET_PROCESS   false




/* TCP/IP RTOS Configurations*/
#define TCPIP_RTOS_STACK_SIZE                1024
#define TCPIP_RTOS_PRIORITY             1



/*** SNTP Configuration ***/
#define TCPIP_STACK_USE_SNTP_CLIENT
#define TCPIP_NTP_DEFAULT_IF		        	"PIC32MZW1"
#define TCPIP_NTP_VERSION             			4
#define TCPIP_NTP_DEFAULT_CONNECTION_TYPE   	IP_ADDRESS_TYPE_IPV4
#define TCPIP_NTP_EPOCH		                	2208988800ul
#define TCPIP_NTP_REPLY_TIMEOUT		        	6
#define TCPIP_NTP_MAX_STRATUM		        	15
#define TCPIP_NTP_TIME_STAMP_TMO				660
#define TCPIP_NTP_SERVER		        		"pool.ntp.org"
#define TCPIP_NTP_SERVER_MAX_LENGTH				30
#define TCPIP_NTP_QUERY_INTERVAL				600
#define TCPIP_NTP_FAST_QUERY_INTERVAL	    	14
#define TCPIP_NTP_TASK_TICK_RATE				10
#define TCPIP_NTP_RX_QUEUE_LIMIT				2



/*** wolfCrypt Library Configuration ***/
#define MICROCHIP_PIC32
#define MICROCHIP_MPLAB_HARMONY
#define MICROCHIP_MPLAB_HARMONY_3
#define HAVE_MCAPI
#define SIZEOF_LONG_LONG 8
#define WOLFSSL_USER_IO
#define NO_WRITEV
#define NO_FILESYSTEM
#define USE_FAST_MATH
#define NO_PWDBASED
#define HAVE_MCAPI
#define WOLF_CRYPTO_CB  // provide call-back support
#define WOLFSSL_MICROCHIP_PIC32MZ
// ---------- CRYPTO HARDWARE MANIFEST START ----------
#define WOLFSSL_HAVE_MCHP_HW_CRYPTO_ECC_HW_BA414E
#define WOLFSSL_HAVE_MCHP_BA414E_CRYPTO
// ---------- CRYPTO HARDWARE MANIFEST END ----------
// ---------- FUNCTIONAL CONFIGURATION START ----------
#define WOLFSSL_AES_SMALL_TABLES
#define WOLFSSL_PIC32MZ_HASH
#define WOLFSSL_PIC32MZ_HASH
#define WOLFSSL_PIC32MZ_HASH
#define HAVE_HKDF
#define NO_DES3
#define WOLFSSL_AES_128
#define WOLFSSL_AES_192
#define WOLFSSL_AES_256
#define WOLFSSL_AES_DIRECT
#define HAVE_AES_DECRYPT
#define HAVE_AES_ECB
#define HAVE_AES_CBC
#define WOLFSSL_AES_COUNTER
#define WOLFSSL_AES_OFB
#define HAVE_AESGCM
#define NO_RC4
#define NO_HC128
#define NO_RABBIT
#define HAVE_ECC
#define HAVE_X963_KDF
#define HAVE_ECC_ENCRYPT
#define HAVE_DH
#define NO_DSA
#define FP_MAX_BITS 4096
#define USE_CERT_BUFFERS_2048
#define WC_RSA_PSS
#define NO_DEV_RANDOM
#define HAVE_HASHDRBG
#define WC_NO_HARDEN
#define SINGLE_THREADED
#define NO_SIG_WRAPPER
#define NO_ERROR_STRINGS
#define NO_WOLFSSL_MEMORY
// ---------- FUNCTIONAL CONFIGURATION END ----------

/* Maximum instances of MSD function driver */
#define USB_DEVICE_MSD_INSTANCES_NUMBER     1 

#define USB_DEVICE_MSD_NUM_SECTOR_BUFFERS 4


/* Number of Logical Units */
#define USB_DEVICE_MSD_LUNS_NUMBER      1



/* WIFI System Service Configuration Options */
#define SYS_WIFI_DEVMODE        			SYS_WIFI_AP


#define SYS_WIFI_MAX_CBS					2
#define SYS_WIFI_COUNTRYCODE        	   "GEN"
#define SYS_WIFI_STA_SSID        			"DEMO_AP"
#define SYS_WIFI_STA_PWD        			"password"


#define SYS_WIFI_STA_AUTHTYPE				SYS_WIFI_WPAWPA2MIXED 



#define SYS_WIFI_STA_AUTOCONNECT   			true


#define SYS_WIFI_AP_SSID					"DEMO_AP_SOFTAP"
#define SYS_WIFI_AP_PWD        				"password"
#define SYS_WIFI_AP_AUTHTYPE				SYS_WIFI_WPA2
#define SYS_WIFI_AP_CHANNEL					1
#define SYS_WIFI_AP_SSIDVISIBILE   			true


#define SYS_WIFI_SCAN_CHANNEL               0
#define SYS_WIFI_SCAN_MAX_SSID_COUNT    	DRV_PIC32MZW_MAX_HIDDEN_SITES
#define SYS_WIFI_SCAN_MODE                  SYS_WIFI_SCAN_MODE_ACTIVE
#define SYS_WIFI_SCAN_SSID_LIST             ""
#define SYS_WIFI_SCAN_SSID_DELIM_CHAR       ','
#define SYS_WIFI_SCAN_CHANNEL24_MASK        0x1fff
#define SYS_WIFI_SCAN_NUM_SLOTS             1
#define SYS_WIFI_SCAN_ACTIVE_SLOT_TIME      20
#define SYS_WIFI_SCAN_PASSIVE_SLOT_TIME     120
#define SYS_WIFI_SCAN_NUM_PROBES            1
#define SYS_WIFI_SCAN_MATCH_MODE        	WDRV_PIC32MZW_SCAN_MATCH_MODE_FIND_ALL




/* SYS WIFI RTOS Configurations*/
#define SYS_WIFI_RTOS_SIZE           		1024
#define SYS_WIFI_RTOS_PRIORITY             1

#define TCPIP_STACK_NETWORK_INTERAFCE_COUNT  	2







// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // CONFIGURATION_H
/*******************************************************************************
 End of File
*/
