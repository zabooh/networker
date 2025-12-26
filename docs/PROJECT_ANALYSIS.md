# Project Analysis: Networker WFI32 - Components and Relationships

## Overview

This project is an MPLAB® Harmony 3 Wireless application for the PIC32MZ W1 family (WFI32E01 microcontroller). It demonstrates a comprehensive IoT solution with Wi-Fi connectivity, web interface, USB mass storage, and MQTT communication.

## Main Components

### 1. Firmware Components (`apps/wifi_easy_config/firmware/src/`)

#### 1.1 Main Application (`main.c`)
- **Purpose**: Application entry point
- **Functionality**: 
  - Initializes all system modules via `SYS_Initialize()`
  - Runs main loop with `SYS_Tasks()` for all MPLAB Harmony modules
- **Relationships**: Orchestrates all other modules

#### 1.2 WiFi Application Module (`app.c` / `app.h`)
- **Purpose**: Core logic for WiFi management and configuration
- **State Machine**:
  - `APP_STATE_INIT`: Initialization, registers WiFi callbacks
  - `APP_STATE_GETCONFIG`: Reads WiFi configuration
  - `APP_STATE_SERVICE_TASKS`: Main operation mode
- **Main Functions**:
  - `WiFiServCallback()`: Handles WiFi events (CONNECT, DISCONNECT, PROVCONFIG)
  - Supports AP mode (Access Point) and STA mode (Station)
  - LED control for visual feedback (Green=connected, Red=disconnected)
- **Relationships**: 
  - Uses System WiFi Service (`SYS_WIFI_*` APIs)
  - Communicates with WiFi Provisioning System

#### 1.3 USB Mass Storage Device Application (`msd_app.c` / `msd_app.h`)
- **Purpose**: Presents SPI Flash as USB mass storage
- **Functionality**:
  - Automatically formats SPI Flash with FAT12 filesystem
  - Appears on PC as separate drive
  - Hosts web page files on this drive
  - Write speed: ~30 KB/s
- **State Machine**:
  - `MSD_APP_STATE_INIT`: Initialization
  - `MSD_APP_STATE_CHECK_FS`: Check filesystem
  - `MSD_APP_STATE_MOUNT_FS`: Mount filesystem
  - `MSD_APP_CONNECT_USB`: Establish USB connection
- **Relationships**: 
  - Accesses SPI Flash via system services
  - Provides web content for HTTP server

#### 1.4 MQTT Application (`app_mqtt.c` / `app_mqtt.h`)
- **Purpose**: MQTT client functionality for IoT communication
- **Functionality**:
  - Connection to MQTT broker
  - Publish/Subscribe messages
  - Status monitoring
- **API**:
  - `APP_MQTT_Initialize()`: MQTT initialization
  - `APP_MQTT_PublishMsg()`: Publish message
  - `APP_MQTT_GetStatus()`: Get status
- **Relationships**: Uses Paho MQTT Embedded C Library

#### 1.5 WebSocket Server System (`config/*/system/wss/`)
- **Purpose**: WebSocket communication for real-time data exchange
- **Functionality**:
  - WebSocket server implementation per RFC 6455
  - Handshake processing (Sec-WebSocket-Key, GUID)
  - Bidirectional JSON data transfer
  - Enables proactive push of data to browser
- **Relationships**: 
  - Works with HTTP server
  - Communicates with web interface

#### 1.6 HTTP/Web Server (`mpfs_net_img.c`)
- **Purpose**: Serve web interface
- **Functionality**:
  - Serves static web pages from SPI Flash
  - Dynamic content generation
  - WiFi configuration interface
- **Relationships**: Loads content from USB MSD / SPI Flash

#### 1.7 Logger (`logger.c` / `logger.h`)
- **Purpose**: Debugging and diagnostics
- **Functionality**: Logging via UART/Console
- **Relationships**: Used by all modules

### 2. Web Interface Components

#### 2.1 WebPage (`apps/wifi_easy_config/WebPage/`)
- **Purpose**: Production web interface for end application
- **Main Files**:
  - `config.htm`: WiFi configuration form
    - Scan and connect to WiFi networks
    - STA/AP mode configuration
    - Static WiFi parameters
    - Network details display
  - `check.html`: Status and monitoring
  - `header.inc` / `footer.inc`: Common UI elements
  - `images/`: Graphics and icons
- **Relationships**: 
  - Copied to SPI Flash via USB MSD
  - Communicates with firmware via HTTP POST and WebSocket

#### 2.2 WebApp (`apps/wifi_easy_config/WebApp/`)
- **Purpose**: Development/design project for web interface
- **Files**:
  - `WFI32.bsdesign`: Bootstrap Studio design project
  - `Export/`: Exported web assets
  - `gzip/`: Compressed versions for storage efficiency
- **Relationships**: Source for WebPage generation

#### 2.3 Python WebSocket Clients (`apps/wifi_easy_config/Pyhton/`)
- **Purpose**: Test and demo clients for WebSocket connection
- **Files**:
  - `simple_wss_client.py`: Simple WebSocket client
  - `wss_client.py`: Advanced WebSocket client
- **Functionality**: Connect to WFI32 WebSocket server on port 8000
- **Relationships**: Testing/debugging of WebSocket server

### 3. Certificates and Security (`apps/wifi_easy_config/certs/`)

- **Purpose**: SSL/TLS certificates for secure communication
- **Files**:
  - `ca_cert.h` / `ca.h`: Certificate Authority
  - `server_cert.h` / `server_key.h`: Server certificates
  - `client_cert.h` / `client_key.h`: Client certificates
  - `device-certs.h`: Device-specific certificates
- **Relationships**: 
  - Used by WolfSSL for secure connections
  - For HTTPS and Secure WebSocket (WSS)

### 4. Build System and Project Files

#### 4.1 MPLAB X Project (`firmware/pic32mz_w1_curiosity_freertos.X/`)
- **Purpose**: IDE project files for build process
- **Components**:
  - Build configurations
  - Linker scripts
  - Project settings
- **Relationships**: Builds all firmware components together

#### 4.2 Disk Image Generator (`apps/wifi_easy_config/disk_image/`)
- **Purpose**: Creates SPI Flash images with web content
- **Files**:
  - `vfat.c`: FAT filesystem generator
  - `mpfs_img2.c`: MPFS image generator
  - `http_print.c`: HTTP content processor
- **Relationships**: Converts WebPage to Flash image

#### 4.3 Setup Scripts
- **`git_clone_h3.bat` / `git_clone_h3.sh`**:
  - **Purpose**: Automatically clone all Harmony 3 framework repositories
  - **Functionality**: 
    - Creates `h3/` directory next to `networker/`
    - Clones all required dependencies
  - **Relationships**: Required for MCC (MPLAB Code Configurator)

### 5. Framework Dependencies (`package.xml`)

The project requires the following MPLAB Harmony 3 modules:

1. **bsp** (v3.13.0): Board Support Package
2. **CMSIS-FreeRTOS** (v10.4.6): Real-Time Operating System
3. **core** (v3.11.1): Core libraries
4. **crypto** (v3.7.6): Cryptography libraries
5. **cryptoauthlib** (v3.3.3): Secure Element library
6. **csp** (v3.14.0): Chip Support Package
7. **dev_packs** (v3.13.1): Device Family Packs
8. **net** (v3.8.0): TCP/IP Stack
9. **paho.mqtt.embedded-c** (v1.2.3): MQTT Client Library
10. **usb** (v3.10.0): USB Device/Host Stack
11. **wireless_wifi** (v3.7.0): WiFi drivers and services
12. **wireless_system_pic32mzw1_wfi32e01** (v3.6.1): WiFi System Services
13. **wolfssl** (v4.7.0): SSL/TLS Library

## Architecture and Data Flow

### Communication Flow

```
User (Browser/Mobile)
    |
    | HTTP(S) Access
    ↓
[WebSocket Connection] ←→ [HTTP Server] ←→ [WebSocket Server]
    |                           |                    |
    | JSON Data                 | Web Files          |
    ↓                           ↓                    ↓
[WiFi Service] ←→ [TCPIP Stack] ←→ [System Services]
    |
    | WiFi Events
    ↓
[APP Module] → [MQTT Client] → [Internet/Cloud]
    |
    ↓
[USB MSD] ←→ [SPI Flash / FAT12] ←→ [Web Content]
```

### Operating Modes

#### 1. Access Point (AP) Mode - WiFi Provisioning
1. Device starts in SoftAP mode
2. User connects to device AP (e.g., "DEMO_AP_SOFTAP")
3. Provisioning via:
   - **HTTP/WebPage**: Browser-based configuration at 192.168.1.1
   - **TCP Socket**: JSON data on port 6666
   - **Mobile App**: Dedicated Android/iOS app
   - **Command Line**: UART commands (wifiprov set ...)
4. Device saves configuration in NVM (Non-Volatile Memory)
5. Auto-reboot
6. Device switches to STA mode

#### 2. Station (STA) Mode - Normal Operation
1. Device connects to configured Home AP
2. Receives IP address via DHCP
3. Starts HTTP server and WebSocket server
4. USB MSD available for web content updates
5. MQTT communication to cloud services
6. Bidirectional data transfer via WebSocket

### Web Interface Integration

1. **Initial Load**:
   - Browser loads static HTML/CSS/JS from HTTP server
   - Files come from SPI Flash (loaded via USB MSD)

2. **WebSocket Connection**:
   - JavaScript initiates WebSocket to `ws://[device-ip]:8000`
   - Handshake per RFC 6455
   - Persistent bidirectional connection

3. **Data Exchange**:
   - **Device → Browser**: Proactive updates (sensor data, status)
   - **Browser → Device**: User commands, configuration
   - Format: JSON for structured data

4. **Content Updates**:
   - Create new web design in Bootstrap Studio
   - Export to WebPage/
   - Copy to device via USB MSD
   - Automatic reload on next browser access

## Development Workflow

### 1. Setup
```bash
# Clone repository
git clone https://github.com/zabooh/networker.git

# Get framework dependencies
cd networker/apps/wifi_easy_config
./git_clone_h3.sh  # or .bat on Windows
```

### 2. Firmware Development
- Open MPLAB X IDE
- Project: `firmware/pic32mz_w1_curiosity_freertos.X`
- MCC (MPLAB Code Configurator) for system configuration
- Edit C code in `firmware/src/`
- Build and flash to PIC32MZ W1 Curiosity Board

### 3. Web Interface Development
- Open Bootstrap Studio: `WebApp/WFI32.bsdesign`
- Customize design
- Export to `WebApp/Export/`
- Copy files to `WebPage/`
- Transfer to device via USB MSD

### 4. Testing
- UART Console (115200 8N1) for logs
- Web browser for UI testing
- Python WebSocket clients for protocol testing
- Packet Sender for TCP Socket provisioning

## Technical Highlights

### Multi-Threading with FreeRTOS
- Separate tasks for WiFi, USB, HTTP, WebSocket, MQTT
- Event-based communication between tasks
- Priority-based scheduling

### Memory Management
- **SPI Flash**: Web content, configuration (persistent)
- **RAM**: Runtime data, buffers
- **NVM**: WiFi credentials, device settings

### Security Features
- WPA2/WPA3 WiFi encryption
- WolfSSL for TLS/SSL
- Optional: Secure Elements (TrustFlex) for certificates
- Secure WebSocket connections (WSS)

### Power Management
- Low-power modes supported
- WiFi Sleep Modes: WSM (WiFi Sleep Mode), WDS (WiFi Deep Sleep)
- Relevant for battery-powered applications

## Summary of Relationships

1. **Main → All Modules**: Orchestration via MPLAB Harmony Task System
2. **WiFi App ↔ System WiFi Service**: Configuration and event handling
3. **HTTP Server ↔ USB MSD**: Web content provisioning
4. **WebSocket Server ↔ Web Browser**: Real-time communication
5. **MQTT Client → Cloud**: IoT data transmission
6. **All Modules → Logger**: Debug output
7. **Bootstrap Studio → WebPage → SPI Flash**: Web design pipeline
8. **Python Clients → WebSocket Server**: Test and development
9. **Framework Dependencies**: All modules use Harmony 3 services

This architecture enables a flexible, extensible IoT solution with modern web technology and professional embedded framework.
