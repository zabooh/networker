# Networker WFI32 - Architecture Diagram

## System Overview

```
┌────────────────────────────────────────────────────────────────────────────┐
│                         Users / External Systems                            │
├──────────────┬──────────────┬──────────────┬─────────────────┬─────────────┤
│   Browser    │  Mobile App  │ Python Test  │  Packet Sender  │ MQTT Broker │
│ (WebSocket)  │   (Socket)   │   Client     │  (TCP Socket)   │   (Cloud)   │
└──────┬───────┴──────┬───────┴──────┬───────┴────────┬────────┴──────┬──────┘
       │              │              │                │               │
       │ HTTP/WSS     │ TCP/IP       │ WebSocket      │ JSON/TCP      │ MQTT
       │              │              │                │               │
┌──────▼──────────────▼──────────────▼────────────────▼───────────────▼──────┐
│                        PIC32MZ W1 (WFI32E01)                                │
│                                                                             │
│  ┌───────────────────────────────────────────────────────────────────────┐ │
│  │                      Application Layer                                │ │
│  │                                                                       │ │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐            │ │
│  │  │ app.c    │  │msd_app.c │  │app_mqtt.c│  │ logger.c │            │ │
│  │  │          │  │          │  │          │  │          │            │ │
│  │  │ WiFi     │  │USB MSD   │  │MQTT      │  │Debug     │            │ │
│  │  │Management│  │Fat12 FS  │  │Client    │  │Console   │            │ │
│  │  └────┬─────┘  └────┬─────┘  └────┬─────┘  └──────────┘            │ │
│  │       │             │             │                                 │ │
│  └───────┼─────────────┼─────────────┼─────────────────────────────────┘ │
│          │             │             │                                    │
│  ┌───────▼─────────────▼─────────────▼─────────────────────────────────┐ │
│  │                    Middleware Layer                                  │ │
│  │                                                                       │ │
│  │  ┌─────────────┐  ┌──────────────┐  ┌────────────────────────────┐ │ │
│  │  │HTTP Server  │  │WebSocket Srv │  │  WiFi Provisioning Svc    │ │ │
│  │  │             │  │              │  │                            │ │ │
│  │  │mpfs_net_img │  │sys_wss.c     │  │  - CLI                     │ │ │
│  │  │             │  │(RFC 6455)    │  │  - Socket                  │ │ │
│  │  │Serves Web   │  │Bidirectional │  │  - HTTP                    │ │ │
│  │  │Pages        │  │JSON          │  │  - Mobile App              │ │ │
│  │  └─────┬───────┘  └──────┬───────┘  └────────┬───────────────────┘ │ │
│  │        │                 │                    │                     │ │
│  └────────┼─────────────────┼────────────────────┼─────────────────────┘ │
│           │                 │                    │                        │
│  ┌────────▼─────────────────▼────────────────────▼─────────────────────┐ │
│  │                 MPLAB Harmony 3 Framework                            │ │
│  │                                                                       │ │
│  │  ┌───────────┐  ┌──────────┐  ┌─────────┐  ┌──────────────────┐   │ │
│  │  │TCP/IP     │  │WiFi      │  │USB      │  │FreeRTOS          │   │ │
│  │  │Stack      │  │Service   │  │Device   │  │(Multitasking)    │   │ │
│  │  │(net)      │  │(wireless)│  │Stack    │  │(CMSIS-FreeRTOS)  │   │ │
│  │  └─────┬─────┘  └────┬─────┘  └────┬────┘  └──────────────────┘   │ │
│  │        │             │             │                                │ │
│  │  ┌─────▼─────┐  ┌────▼─────┐  ┌────▼────┐  ┌──────────────────┐   │ │
│  │  │WolfSSL    │  │Paho MQTT │  │Crypto   │  │System Services   │   │ │
│  │  │(TLS/SSL)  │  │Embedded-C│  │Libraries│  │(BSP, CSP, Core)  │   │ │
│  │  └───────────┘  └──────────┘  └─────────┘  └──────────────────┘   │ │
│  │                                                                       │ │
│  └───────────────────────────────────────────────────────────────────────┘ │
│                                                                             │
│  ┌───────────────────────────────────────────────────────────────────────┐ │
│  │                      Hardware Abstraction Layer                       │ │
│  │                                                                       │ │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌────────────────────┐  │ │
│  │  │WiFi      │  │SPI Flash │  │USB       │  │UART (Debug)        │  │ │
│  │  │Radio     │  │(Web Data)│  │Device    │  │(Console)           │  │ │
│  │  │(WPA2/3)  │  │(4MB)     │  │(MSD)     │  │(115200 8N1)        │  │ │
│  │  └──────────┘  └──────────┘  └──────────┘  └────────────────────┘  │ │
│  │                                                                       │ │
│  └───────────────────────────────────────────────────────────────────────┘ │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘

┌────────────────────────────────────────────────────────────────────────────┐
│                          Development Tools                                  │
├─────────────────┬────────────────┬─────────────────┬──────────────────────┤
│ Bootstrap Studio│ MPLAB X IDE   │ MPLAB Code      │ USB Connection       │
│ (Web Design)    │ (Firmware)     │ Configurator    │ (Web Upload)         │
│                 │                │ (MCC)           │                      │
│    WFI32.bsdesign → firmware/*.X → System Config   → WebPage → SPI Flash  │
└─────────────────┴────────────────┴─────────────────┴──────────────────────┘
```

## Data Flow Scenarios

### Scenario 1: WiFi Provisioning (Initial Setup)

```
┌─────────┐                                              ┌──────────────┐
│  User   │                                              │   WFI32      │
└────┬────┘                                              └──────┬───────┘
     │                                                          │
     │ 1. Device boots                                         │
     │                    <─────────────────────────────────────┤ AP Mode
     │                       LED: Red (not connected)          │
     │                                                          │
     │ 2. Connect to "DEMO_AP_SOFTAP"                          │
     ├──────────────────────────────────────────────────────>  │
     │                                                          │
     │                    <─────────────────────────────────────┤
     │                       IP: 192.168.1.100 (DHCP)          │
     │                                                          │
     │ 3. Open browser: http://192.168.1.1                     │
     ├──────────────────────────────────────────────────────>  │
     │                                                          │
     │                    <─────────────────────────────────────┤
     │                       config.htm (HTTP Server)          │
     │                                                          │
     │ 4. Enter Home WiFi Credentials                          │
     │    {SSID: "MyHomeWiFi", PWD: "secret", auth: WPA2}     │
     ├──────────────────────────────────────────────────────>  │
     │                       HTTP POST                          │
     │                                                   ┌──────┴──────┐
     │                                                   │ WiFi Prov   │
     │                                                   │ Service     │
     │                                                   │ - Parse JSON│
     │                                                   │ - Save NVM  │
     │                    <─────────────────────────────┤ - Reboot    │
     │                       Confirmation + Reboot      └──────┬──────┘
     │                                                          │
     │ 5. Device restarted in STA Mode                         │
     │                    <─────────────────────────────────────┤ STA Mode
     │                                                   ┌──────┴──────┐
     │                                                   │ Connect to  │
     │                                                   │ MyHomeWiFi  │
     │                                                   │ Get IP DHCP │
     │                    <─────────────────────────────┤ LED: Green  │
     │                       IP: 192.168.0.42 (DHCP)    └──────┬──────┘
     │                                                          │
     │ 6. Connect to MyHomeWiFi                                │
     ├──────────────────────────────────────────────────────>  │
     │                                                          │
     │ 7. Browser: http://192.168.0.42                         │
     ├──────────────────────────────────────────────────────>  │
     │                    <─────────────────────────────────────┤
     │                       Web Interface loaded              │
```

### Scenario 2: WebSocket Real-time Communication

```
┌─────────┐                              ┌──────────────┐
│ Browser │                              │   WFI32      │
└────┬────┘                              └──────┬───────┘
     │                                          │
     │ 1. Initialize WebSocket                  │
     │    ws://192.168.0.42:8000                │
     ├──────────────────────────────────────>   │
     │          HTTP Upgrade Request            │
     │                                   ┌──────┴──────┐
     │                                   │ sys_wss     │
     │                                   │ - Handshake │
     │                                   │ - RFC 6455  │
     │                  <────────────────┤ - Sec Key   │
     │          101 Switching Protocols  └──────┬──────┘
     │                                          │
     │ 2. Persistent connection established     │
     │    ═══════════════════════════════════  │
     │                                          │
     │ 3. Send sensor data (e.g. Button)        │
     │    {type:"button", value: "pressed"}    │
     ├──────────────────────────────────────>  │
     │          WebSocket Frame (JSON)   ┌──────┴──────┐
     │                                   │ app.c       │
     │                                   │ - Parse JSON│
     │                                   │ - Action    │
     │                  <────────────────┤ - Prepare   │
     │    {type:"ack", status: "ok"}    └──────┬──────┘
     │          WebSocket Frame (JSON)          │
     │                                          │
     │ 4. Proactive updates from device         │
     │                                   ┌──────┴──────┐
     │                                   │ app.c       │
     │                                   │ - Event     │
     │                  <────────────────┤ - Push Data │
     │ {type:"temp", value: 23.5, unit:"C"}    │      │
     │          WebSocket Frame (JSON)   └──────┬──────┘
     │                                          │
     │ 5. UI Update in browser                  │
     ├─────────────────┐                        │
     │ Display: 23.5°C │                        │
     └─────────────────┘                        │
```

### Scenario 3: Web Content Update via USB MSD

```
┌────────────────┐              ┌──────────────┐
│ Developer PC   │              │   WFI32      │
└────────┬───────┘              └──────┬───────┘
         │                             │
         │ 1. Connect USB cable        │
         ├─────────────────────────>   │
         │                      ┌──────┴──────┐
         │                      │ msd_app.c   │
         │                      │ - Init USB  │
         │                      │ - Mount FS  │
         │  <───────────────────┤ - Present   │
         │    New drive "E:"       MSD        │
         │    (FAT12 Filesystem) └──────┬──────┘
         │                             │
         │ 2. Bootstrap Studio         │
         │    - Change design          │
         │    - Export → WebApp/Export/│
         ├─────────────────┐           │
         │  WFI32.bsdesign │           │
         │  ↓              │           │
         │  Export/        │           │
         │  - index.html   │           │
         │  - assets/...   │           │
         └─────────────────┘           │
         │                             │
         │ 3. Copy files               │
         │    WebPage/ → E:\           │
         ├─────────────────────────>   │
         │                      ┌──────┴──────┐
         │                      │ SPI Flash   │
         │                      │ - Write     │
         │  <───────────────────┤ - Update    │
         │    Copy complete (30KB/s)  │       │
         │                      └──────┬──────┘
         │                             │
         │ 4. Disconnect USB           │
         ├─────────────────────────>   │
         │                      ┌──────┴──────┐
         │                      │ HTTP Server │
         │                      │ - Reload    │
         │                      │ - New Files │
         │                      └──────┬──────┘
         │                             │
         │ 5. Browser Refresh          │
         │    http://192.168.0.42      │
         ├─────────────────────────>   │
         │  <───────────────────────────┤
         │    New web interface        │
```

## Component Interaction Matrix

| From ↓ / To → | WiFi App | HTTP Srv | WSS Srv | USB MSD | MQTT | Logger | System Svc |
|---------------|----------|----------|---------|---------|------|--------|------------|
| **main.c**    | Init/Task| Init/Task| Init/Task| Init/Task| Init/Task| Init | Init/Task  |
| **WiFi App**  | -        | Config   | Events  | -       | Trigger| Debug  | WiFi Ctrl  |
| **HTTP Srv**  | Request  | -        | Upgrade | Content | -    | Debug  | TCP/IP     |
| **WSS Srv**   | Push Data| -        | -       | -       | -    | Debug  | TCP/IP     |
| **USB MSD**   | -        | Files    | -       | -       | -    | Debug  | FS/USB     |
| **MQTT**      | Status   | -        | -       | -       | -    | Debug  | TCP/IP     |
| **User**      | Prov     | Web UI   | JSON    | Upload  | Cloud| Console| -          |

## State Machine Overview

### WiFi Application State Machine (app.c)

```
    START
      │
      ▼
┌───────────────┐
│ APP_STATE_    │ → Register WiFi Callback
│ INIT          │   LED Red On
└───────┬───────┘
        │
        ▼
┌───────────────┐
│ APP_STATE_    │ → Get WiFi Config
│ GETCONFIG     │   (AP or STA mode?)
└───────┬───────┘
        │
        ▼
┌───────────────┐
│ APP_STATE_    │ → Service Mode
│ SERVICE_TASKS │   Wait for events
└───────┬───────┘
        │
        └──────────────┐
                       │
    ┌──────────────────▼──────────────────┐
    │      WiFi Event Callbacks           │
    ├─────────────────────────────────────┤
    │ SYS_WIFI_CONNECT:                   │
    │   → LED Green On                    │
    │   → Log IP Address                  │
    ├─────────────────────────────────────┤
    │ SYS_WIFI_DISCONNECT:                │
    │   → LED Red On                      │
    │   → Log Disconnect                  │
    ├─────────────────────────────────────┤
    │ SYS_WIFI_PROVCONFIG:                │
    │   → Save Config                     │
    │   → Log New Settings                │
    └─────────────────────────────────────┘
```

### USB MSD Application State Machine (msd_app.c)

```
    START
      │
      ▼
┌───────────────┐
│ MSD_APP_STATE_│ → Init USB System
│ INIT          │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│ MSD_APP_STATE_│ → Check Switch
│ CHECK_SWITCH  │   (User input?)
└───────┬───────┘
        │
        ▼
┌───────────────┐
│ MSD_APP_STATE_│ → Check if FS exists
│ CHECK_FS      │
└───────┬───────┘
        │
        ├── FS exists ──┐
        │               │
        │               ▼
        │          ┌───────────────┐
        │          │ MSD_APP_STATE_│ → Mount Filesystem
        │          │ MOUNT_FS      │
        │          └───────┬───────┘
        │                  │
        └── FS missing ────┤
                          │
                          ▼
                    ┌───────────────┐
                    │ MSD_APP_STATE_│ → Format with FAT12
                    │ CLEAR_DRIVE   │   Initialize root dir
                    └───────┬───────┘
                            │
                            ▼
                    ┌───────────────┐
                    │ MSD_APP_      │ → Connect USB to PC
                    │ CONNECT_USB   │   Present as MSD
                    └───────┬───────┘
                            │
                            ▼
                    ┌───────────────┐
                    │ MSD_APP_STATE_│ → Service Mode
                    │ SERVICE_TASKS │   Handle USB Events
                    └───────────────┘
```

## Memory Layout

```
┌────────────────────────────────────────────────────────────┐
│                     SPI Flash (4MB)                        │
├────────────────────────────────────────────────────────────┤
│  ┌──────────────────────────────────────────────────────┐ │
│  │ FAT12 Filesystem                                     │ │
│  ├──────────────────────────────────────────────────────┤ │
│  │ Root Directory:                                      │ │
│  │   - index.html                                       │ │
│  │   - config.htm                                       │ │
│  │   - check.html                                       │ │
│  │   - header.inc                                       │ │
│  │   - footer.inc                                       │ │
│  │   - favicon.ico                                      │ │
│  │   - images/                                          │ │
│  │   - assets/ (CSS, JS)                                │ │
│  │   - DynRcrd.bin                                      │ │
│  │   - FileRcrd.bin                                     │ │
│  └──────────────────────────────────────────────────────┘ │
└────────────────────────────────────────────────────────────┘

┌────────────────────────────────────────────────────────────┐
│                RAM (Runtime Memory)                        │
├────────────────────────────────────────────────────────────┤
│  ┌──────────────────────────────────────────────────────┐ │
│  │ FreeRTOS Heap                                        │ │
│  │   - Task Stacks                                      │ │
│  │   - Queue Buffers                                    │ │
│  │   - Semaphores                                       │ │
│  ├──────────────────────────────────────────────────────┤ │
│  │ TCP/IP Buffers                                       │ │
│  │   - RX/TX Buffers                                    │ │
│  │   - Socket Buffers                                   │ │
│  ├──────────────────────────────────────────────────────┤ │
│  │ Application Data                                     │ │
│  │   - appData (APP_DATA struct)                        │ │
│  │   - wificonfig (SYS_WIFI_CONFIG)                     │ │
│  │   - WebSocket Connections                            │ │
│  │   - HTTP Sessions                                    │ │
│  └──────────────────────────────────────────────────────┘ │
└────────────────────────────────────────────────────────────┘

┌────────────────────────────────────────────────────────────┐
│              NVM (Non-Volatile Memory)                     │
├────────────────────────────────────────────────────────────┤
│  ┌──────────────────────────────────────────────────────┐ │
│  │ WiFi Configuration                                   │ │
│  │   - Mode (AP/STA)                                    │ │
│  │   - SSID                                             │ │
│  │   - Password                                         │ │
│  │   - Auth Type                                        │ │
│  │   - Channel                                          │ │
│  │   - Country Code                                     │ │
│  │   - Auto-Connect Flag                                │ │
│  └──────────────────────────────────────────────────────┘ │
└────────────────────────────────────────────────────────────┘
```

## Task Priorities (FreeRTOS)

```
Highest Priority
    ↑
    │   ┌──────────────────────────────┐
    │   │ WiFi Driver Task             │ (Critical)
    │   │ - WiFi Radio Management      │
    │   │ - Low-level WiFi Protocol    │
    │   └──────────────────────────────┘
    │
    │   ┌──────────────────────────────┐
    │   │ TCP/IP Stack Task            │ (High)
    │   │ - Packet Processing          │
    │   │ - Protocol Handling          │
    │   └──────────────────────────────┘
    │
    │   ┌──────────────────────────────┐
    │   │ USB Device Task              │ (High)
    │   │ - USB Protocol               │
    │   │ - MSD Operations             │
    │   └──────────────────────────────┘
    │
    │   ┌──────────────────────────────┐
    │   │ Application Task (APP_Tasks) │ (Medium)
    │   │ - User Logic                 │
    │   │ - WiFi Events                │
    │   └──────────────────────────────┘
    │
    │   ┌──────────────────────────────┐
    │   │ MQTT Task                    │ (Medium)
    │   │ - MQTT Protocol              │
    │   │ - Message Queue              │
    │   └──────────────────────────────┘
    │
    │   ┌──────────────────────────────┐
    │   │ Logging Task                 │ (Low)
    │   │ - Console Output             │
    │   │ - Debug Messages             │
    │   └──────────────────────────────┘
    ↓
Lowest Priority
```

## Summary

This architecture demonstrates:
- **Modularity**: Clearly separated components with defined interfaces
- **Scalability**: Easy addition of new features (e.g., additional sensors)
- **Robustness**: FreeRTOS for stable multitasking, WolfSSL for security
- **User-Friendliness**: Multiple provisioning methods, modern web UI
- **Developer-Friendliness**: Bootstrap Studio for UI, MCC for hardware configuration

The combination of MPLAB Harmony 3 Framework, FreeRTOS, modern web technology (WebSocket), and flexible provisioning options makes this project a solid foundation for IoT applications.
