# Networker WFI32 - Architektur Diagramm

## System-Übersicht

```
┌────────────────────────────────────────────────────────────────────────────┐
│                          Benutzer / Externe Systeme                         │
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
│                           Entwicklungs-Tools                                │
├─────────────────┬────────────────┬─────────────────┬──────────────────────┤
│ Bootstrap Studio│ MPLAB X IDE   │ MPLAB Code      │ USB Connection       │
│ (Web Design)    │ (Firmware)     │ Configurator    │ (Web Upload)         │
│                 │                │ (MCC)           │                      │
│    WFI32.bsdesign → firmware/*.X → System Config   → WebPage → SPI Flash  │
└─────────────────┴────────────────┴─────────────────┴──────────────────────┘
```

## Datenfluss-Szenarien

### Szenario 1: WiFi Provisioning (Ersteinrichtung)

```
┌─────────┐                                              ┌──────────────┐
│ Benutzer│                                              │   WFI32      │
└────┬────┘                                              └──────┬───────┘
     │                                                          │
     │ 1. Gerät bootet                                         │
     │                    <─────────────────────────────────────┤ AP Mode
     │                       LED: Rot (nicht verbunden)        │
     │                                                          │
     │ 2. Verbinden mit "DEMO_AP_SOFTAP"                       │
     ├──────────────────────────────────────────────────────>  │
     │                                                          │
     │                    <─────────────────────────────────────┤
     │                       IP: 192.168.1.100 (DHCP)          │
     │                                                          │
     │ 3. Browser öffnen: http://192.168.1.1                   │
     ├──────────────────────────────────────────────────────>  │
     │                                                          │
     │                    <─────────────────────────────────────┤
     │                       config.htm (HTTP Server)          │
     │                                                          │
     │ 4. Home WiFi Credentials eingeben                       │
     │    {SSID: "MyHomeWiFi", PWD: "secret", auth: WPA2}     │
     ├──────────────────────────────────────────────────────>  │
     │                       HTTP POST                          │
     │                                                   ┌──────┴──────┐
     │                                                   │ WiFi Prov   │
     │                                                   │ Service     │
     │                                                   │ - Parse JSON│
     │                                                   │ - Save NVM  │
     │                    <─────────────────────────────┤ - Reboot    │
     │                       Bestätigung + Reboot       └──────┬──────┘
     │                                                          │
     │ 5. Gerät neu gestartet im STA Mode                      │
     │                    <─────────────────────────────────────┤ STA Mode
     │                                                   ┌──────┴──────┐
     │                                                   │ Connect to  │
     │                                                   │ MyHomeWiFi  │
     │                                                   │ Get IP DHCP │
     │                    <─────────────────────────────┤ LED: Grün   │
     │                       IP: 192.168.0.42 (DHCP)    └──────┬──────┘
     │                                                          │
     │ 6. Verbinden mit MyHomeWiFi                             │
     ├──────────────────────────────────────────────────────>  │
     │                                                          │
     │ 7. Browser: http://192.168.0.42                         │
     ├──────────────────────────────────────────────────────>  │
     │                    <─────────────────────────────────────┤
     │                       Web Interface geladen             │
```

### Szenario 2: WebSocket Echtzeit-Kommunikation

```
┌─────────┐                              ┌──────────────┐
│ Browser │                              │   WFI32      │
└────┬────┘                              └──────┬───────┘
     │                                          │
     │ 1. WebSocket initialisieren              │
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
     │ 2. Persistente Verbindung etabliert     │
     │    ═══════════════════════════════════  │
     │                                          │
     │ 3. Sensor-Daten senden (z.B. Button)    │
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
     │ 4. Proaktive Updates vom Gerät           │
     │                                   ┌──────┴──────┐
     │                                   │ app.c       │
     │                                   │ - Event     │
     │                  <────────────────┤ - Push Data │
     │ {type:"temp", value: 23.5, unit:"C"}    │      │
     │          WebSocket Frame (JSON)   └──────┬──────┘
     │                                          │
     │ 5. UI Update im Browser                  │
     ├─────────────────┐                        │
     │ Display: 23.5°C │                        │
     └─────────────────┘                        │
```

### Szenario 3: Web-Content Update via USB MSD

```
┌────────────────┐              ┌──────────────┐
│ Entwickler PC  │              │   WFI32      │
└────────┬───────┘              └──────┬───────┘
         │                             │
         │ 1. USB-Kabel verbinden      │
         ├─────────────────────────>   │
         │                      ┌──────┴──────┐
         │                      │ msd_app.c   │
         │                      │ - Init USB  │
         │                      │ - Mount FS  │
         │  <───────────────────┤ - Present   │
         │    Neues Laufwerk "E:"  MSD        │
         │    (FAT12 Filesystem) └──────┬──────┘
         │                             │
         │ 2. Bootstrap Studio         │
         │    - Design ändern          │
         │    - Export → WebApp/Export/│
         ├─────────────────┐           │
         │  WFI32.bsdesign │           │
         │  ↓              │           │
         │  Export/        │           │
         │  - index.html   │           │
         │  - assets/...   │           │
         └─────────────────┘           │
         │                             │
         │ 3. Dateien kopieren         │
         │    WebPage/ → E:\           │
         ├─────────────────────────>   │
         │                      ┌──────┴──────┐
         │                      │ SPI Flash   │
         │                      │ - Write     │
         │  <───────────────────┤ - Update    │
         │    Copy complete (30KB/s)  │       │
         │                      └──────┬──────┘
         │                             │
         │ 4. USB trennen              │
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
         │    Neue Web-Oberfläche      │
```

## Komponenten-Interaktionsmatrix

| Von ↓ / Nach → | WiFi App | HTTP Srv | WSS Srv | USB MSD | MQTT | Logger | System Svc |
|----------------|----------|----------|---------|---------|------|--------|------------|
| **main.c**     | Init/Task| Init/Task| Init/Task| Init/Task| Init/Task| Init | Init/Task  |
| **WiFi App**   | -        | Config   | Events  | -       | Trigger| Debug  | WiFi Ctrl  |
| **HTTP Srv**   | Request  | -        | Upgrade | Content | -    | Debug  | TCP/IP     |
| **WSS Srv**    | Push Data| -        | -       | -       | -    | Debug  | TCP/IP     |
| **USB MSD**    | -        | Files    | -       | -       | -    | Debug  | FS/USB     |
| **MQTT**       | Status   | -        | -       | -       | -    | Debug  | TCP/IP     |
| **User**       | Prov     | Web UI   | JSON    | Upload  | Cloud| Console| -          |

## State-Machine Übersicht

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

## Speicher-Layout

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
│                RAM (Laufzeit-Speicher)                     │
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

## Task-Prioritäten (FreeRTOS)

```
Höchste Priorität
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
Niedrigste Priorität
```

## Zusammenfassung

Diese Architektur zeigt:
- **Modularität**: Klar getrennte Komponenten mit definierten Schnittstellen
- **Skalierbarkeit**: Einfaches Hinzufügen neuer Features (z.B. weitere Sensoren)
- **Robustheit**: FreeRTOS für stabiles Multitasking, WolfSSL für Sicherheit
- **Benutzerfreundlichkeit**: Multiple Provisioning-Methoden, modernes Web-UI
- **Entwickler-Freundlichkeit**: Bootstrap Studio für UI, MCC für Hardware-Konfiguration

Die Kombination aus MPLAB Harmony 3 Framework, FreeRTOS, moderner Web-Technologie (WebSocket) und flexiblen Provisioning-Optionen macht dieses Projekt zu einer soliden Basis für IoT-Anwendungen.
