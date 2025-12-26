# Projektanalyse: Networker WFI32 - Komponenten und Zusammenhänge

## Übersicht

Dieses Projekt ist eine MPLAB® Harmony 3 Wireless-Anwendung für die PIC32MZ W1 Familie (WFI32E01 Mikrocontroller). Es demonstriert eine umfassende IoT-Lösung mit Wi-Fi-Konnektivität, Web-Interface, USB-Massenspeicher und MQTT-Kommunikation.

## Hauptkomponenten

### 1. Firmware-Komponenten (`apps/wifi_easy_config/firmware/src/`)

#### 1.1 Main Application (`main.c`)
- **Zweck**: Einstiegspunkt der Applikation
- **Funktionalität**: 
  - Initialisiert alle System-Module via `SYS_Initialize()`
  - Führt Hauptschleife aus mit `SYS_Tasks()` für alle MPLAB Harmony Module
- **Beziehungen**: Orchestriert alle anderen Module

#### 1.2 WiFi Application Module (`app.c` / `app.h`)
- **Zweck**: Kernlogik für WiFi-Verwaltung und Konfiguration
- **Zustandsmaschine**:
  - `APP_STATE_INIT`: Initialisierung, registriert WiFi-Callbacks
  - `APP_STATE_GETCONFIG`: Liest WiFi-Konfiguration
  - `APP_STATE_SERVICE_TASKS`: Hauptbetriebsmodus
- **Hauptfunktionen**:
  - `WiFiServCallback()`: Behandelt WiFi-Events (CONNECT, DISCONNECT, PROVCONFIG)
  - Unterstützt AP-Modus (Access Point) und STA-Modus (Station)
  - LED-Steuerung für visuelles Feedback (Grün=verbunden, Rot=getrennt)
- **Beziehungen**: 
  - Nutzt System WiFi Service (`SYS_WIFI_*` APIs)
  - Kommuniziert mit WiFi Provisioning System

#### 1.3 USB Mass Storage Device Application (`msd_app.c` / `msd_app.h`)
- **Zweck**: Stellt SPI Flash als USB-Massenspeicher bereit
- **Funktionalität**:
  - Formatiert SPI Flash automatisch mit FAT12 Dateisystem
  - Präsentiert sich am PC als separates Laufwerk
  - Hostet Web-Page-Dateien auf diesem Laufwerk
  - Schreibgeschwindigkeit: ca. 30 KB/s
- **Zustandsmaschine**:
  - `MSD_APP_STATE_INIT`: Initialisierung
  - `MSD_APP_STATE_CHECK_FS`: Dateisystem prüfen
  - `MSD_APP_STATE_MOUNT_FS`: Dateisystem mounten
  - `MSD_APP_CONNECT_USB`: USB-Verbindung herstellen
- **Beziehungen**: 
  - Zugriff auf SPI Flash über System Services
  - Bereitstellung von Web-Inhalten für HTTP Server

#### 1.4 MQTT Application (`app_mqtt.c` / `app_mqtt.h`)
- **Zweck**: MQTT-Client-Funktionalität für IoT-Kommunikation
- **Funktionalität**:
  - Verbindung zu MQTT-Broker
  - Publish/Subscribe von Nachrichten
  - Status-Überwachung
- **API**:
  - `APP_MQTT_Initialize()`: MQTT-Initialisierung
  - `APP_MQTT_PublishMsg()`: Nachricht publizieren
  - `APP_MQTT_GetStatus()`: Status abrufen
- **Beziehungen**: Nutzt Paho MQTT Embedded C Library

#### 1.5 WebSocket Server System (`config/*/system/wss/`)
- **Zweck**: WebSocket-Kommunikation für Echtzeit-Datenaustausch
- **Funktionalität**:
  - WebSocket-Server-Implementierung gemäß RFC 6455
  - Handshake-Verarbeitung (Sec-WebSocket-Key, GUID)
  - Bidirektionale JSON-Datenübertragung
  - Ermöglicht proaktives Push von Daten an Browser
- **Beziehungen**: 
  - Arbeitet mit HTTP Server zusammen
  - Kommuniziert mit Web-Interface

#### 1.6 HTTP/Web Server (`mpfs_net_img.c`)
- **Zweck**: Bereitstellen des Web-Interfaces
- **Funktionalität**:
  - Serviert statische Web-Seiten aus SPI Flash
  - Dynamische Content-Generierung
  - WiFi-Konfigurationsschnittstelle
- **Beziehungen**: Lädt Inhalte von USB MSD / SPI Flash

#### 1.7 Logger (`logger.c` / `logger.h`)
- **Zweck**: Debugging und Diagnose
- **Funktionalität**: Logging über UART/Console
- **Beziehungen**: Wird von allen Modulen genutzt

### 2. Web-Interface-Komponenten

#### 2.1 WebPage (`apps/wifi_easy_config/WebPage/`)
- **Zweck**: Produktive Web-Oberfläche für Endanwendung
- **Hauptdateien**:
  - `config.htm`: WiFi-Konfigurationsformular
    - Scan und Verbindung zu WiFi-Netzwerken
    - STA/AP Modus-Konfiguration
    - Statische WiFi-Parameter
    - Netzwerk-Details-Anzeige
  - `check.html`: Status und Monitoring
  - `header.inc` / `footer.inc`: Gemeinsame UI-Elemente
  - `images/`: Grafiken und Icons
- **Beziehungen**: 
  - Wird auf SPI Flash via USB MSD kopiert
  - Kommuniziert mit Firmware via HTTP POST und WebSocket

#### 2.2 WebApp (`apps/wifi_easy_config/WebApp/`)
- **Zweck**: Entwicklungs-/Design-Projekt für Web-Interface
- **Dateien**:
  - `WFI32.bsdesign`: Bootstrap Studio Designprojekt
  - `Export/`: Exportierte Web-Assets
  - `gzip/`: Komprimierte Versionen für Speichereffizienz
- **Beziehungen**: Source für WebPage-Generierung

#### 2.3 Python WebSocket Clients (`apps/wifi_easy_config/Pyhton/`)
- **Zweck**: Test- und Demo-Clients für WebSocket-Verbindung
- **Dateien**:
  - `simple_wss_client.py`: Einfacher WebSocket-Client
  - `wss_client.py`: Erweiterter WebSocket-Client
- **Funktionalität**: Verbindung zu WFI32 WebSocket-Server auf Port 8000
- **Beziehungen**: Testing/Debugging des WebSocket-Servers

### 3. Zertifikate und Sicherheit (`apps/wifi_easy_config/certs/`)

- **Zweck**: SSL/TLS-Zertifikate für sichere Kommunikation
- **Dateien**:
  - `ca_cert.h` / `ca.h`: Certificate Authority
  - `server_cert.h` / `server_key.h`: Server-Zertifikate
  - `client_cert.h` / `client_key.h`: Client-Zertifikate
  - `device-certs.h`: Gerätespezifische Zertifikate
- **Beziehungen**: 
  - Verwendet von WolfSSL für sichere Verbindungen
  - Für HTTPS und Secure WebSocket (WSS)

### 4. Build-System und Projektdateien

#### 4.1 MPLAB X Projekt (`firmware/pic32mz_w1_curiosity_freertos.X/`)
- **Zweck**: IDE-Projektdateien für Build-Prozess
- **Komponenten**:
  - Build-Konfigurationen
  - Linker-Skripte
  - Projekt-Einstellungen
- **Beziehungen**: Baut alle Firmware-Komponenten zusammen

#### 4.2 Disk Image Generator (`apps/wifi_easy_config/disk_image/`)
- **Zweck**: Erstellt SPI Flash Images mit Web-Inhalten
- **Dateien**:
  - `vfat.c`: FAT-Dateisystem-Generator
  - `mpfs_img2.c`: MPFS Image Generator
  - `http_print.c`: HTTP Content Processor
- **Beziehungen**: Konvertiert WebPage zu Flash-Image

#### 4.3 Setup-Skripte
- **`git_clone_h3.bat` / `git_clone_h3.sh`**:
  - **Zweck**: Automatisches Klonen aller Harmony 3 Framework-Repositories
  - **Funktionalität**: 
    - Erstellt `h3/` Verzeichnis neben `networker/`
    - Klont alle benötigten Abhängigkeiten
  - **Beziehungen**: Erforderlich für MCC (MPLAB Code Configurator)

### 5. Framework-Abhängigkeiten (`package.xml`)

Das Projekt benötigt folgende MPLAB Harmony 3 Module:

1. **bsp** (v3.13.0): Board Support Package
2. **CMSIS-FreeRTOS** (v10.4.6): Real-Time Operating System
3. **core** (v3.11.1): Kern-Bibliotheken
4. **crypto** (v3.7.6): Kryptographie-Bibliotheken
5. **cryptoauthlib** (v3.3.3): Secure Element Bibliothek
6. **csp** (v3.14.0): Chip Support Package
7. **dev_packs** (v3.13.1): Device Family Packs
8. **net** (v3.8.0): TCP/IP Stack
9. **paho.mqtt.embedded-c** (v1.2.3): MQTT Client Library
10. **usb** (v3.10.0): USB Device/Host Stack
11. **wireless_wifi** (v3.7.0): WiFi Treiber und Services
12. **wireless_system_pic32mzw1_wfi32e01** (v3.6.1): WiFi System Services
13. **wolfssl** (v4.7.0): SSL/TLS Bibliothek

## Architektur und Datenfluss

### Kommunikationsablauf

```
Benutzer (Browser/Mobile)
    |
    | HTTP(S) Zugriff
    ↓
[WebSocket Connection] ←→ [HTTP Server] ←→ [WebSocket Server]
    |                           |                    |
    | JSON Daten                | Web Files          |
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

### Betriebsmodi

#### 1. Access Point (AP) Modus - WiFi Provisioning
1. Gerät startet im SoftAP-Modus
2. Benutzer verbindet sich mit Gerät-AP (z.B. "DEMO_AP_SOFTAP")
3. Provisioning über:
   - **HTTP/WebPage**: Browser-basierte Konfiguration auf 192.168.1.1
   - **TCP Socket**: JSON-Daten auf Port 6666
   - **Mobile App**: Dedizierte Android/iOS App
   - **Command Line**: UART-Befehle (wifiprov set ...)
4. Gerät speichert Konfiguration in NVM (Non-Volatile Memory)
5. Auto-Reboot
6. Gerät wechselt zu STA-Modus

#### 2. Station (STA) Modus - Normalbetrieb
1. Gerät verbindet sich mit konfiguriertem Home-AP
2. Erhält IP-Adresse via DHCP
3. Startet HTTP-Server und WebSocket-Server
4. USB MSD verfügbar für Web-Content-Updates
5. MQTT-Kommunikation zu Cloud-Services
6. Bidirektionale Datenübertragung via WebSocket

### Web-Interface-Integration

1. **Initial Load**:
   - Browser lädt statische HTML/CSS/JS von HTTP-Server
   - Dateien kommen aus SPI Flash (via USB MSD geladen)

2. **WebSocket Verbindung**:
   - JavaScript initiiert WebSocket zu `ws://[device-ip]:8000`
   - Handshake gemäß RFC 6455
   - Persistente bidirektionale Verbindung

3. **Datenaustauch**:
   - **Device → Browser**: Proaktive Updates (Sensor-Daten, Status)
   - **Browser → Device**: Benutzer-Befehle, Konfiguration
   - Format: JSON für strukturierte Daten

4. **Content Updates**:
   - Neues Web-Design in Bootstrap Studio erstellen
   - Export nach WebPage/
   - Via USB MSD auf Gerät kopieren
   - Automatisches Reload beim nächsten Browser-Zugriff

## Entwicklungsworkflow

### 1. Setup
```bash
# Repository klonen
git clone https://github.com/zabooh/networker.git

# Framework-Abhängigkeiten holen
cd networker/apps/wifi_easy_config
./git_clone_h3.sh  # oder .bat auf Windows
```

### 2. Firmware-Entwicklung
- MPLAB X IDE öffnen
- Projekt: `firmware/pic32mz_w1_curiosity_freertos.X`
- MCC (MPLAB Code Configurator) für System-Konfiguration
- C-Code in `firmware/src/` bearbeiten
- Build und Flash auf PIC32MZ W1 Curiosity Board

### 3. Web-Interface-Entwicklung
- Bootstrap Studio öffnen: `WebApp/WFI32.bsdesign`
- Design anpassen
- Export nach `WebApp/Export/`
- Dateien nach `WebPage/` kopieren
- Via USB MSD auf Gerät übertragen

### 4. Testing
- UART Console (115200 8N1) für Logs
- Web-Browser für UI-Testing
- Python WebSocket-Clients für Protokoll-Testing
- Packet Sender für TCP Socket Provisioning

## Technische Besonderheiten

### Multi-Threading mit FreeRTOS
- Separate Tasks für WiFi, USB, HTTP, WebSocket, MQTT
- Event-basierte Kommunikation zwischen Tasks
- Priority-basiertes Scheduling

### Speicher-Management
- **SPI Flash**: Web-Content, Konfiguration (persistent)
- **RAM**: Runtime-Daten, Buffers
- **NVM**: WiFi-Credentials, Device-Settings

### Security Features
- WPA2/WPA3 WiFi-Verschlüsselung
- WolfSSL für TLS/SSL
- Optional: Secure Elements (TrustFlex) für Zertifikate
- Sichere WebSocket-Verbindungen (WSS)

### Power Management
- Low-Power Modi unterstützt
- WiFi Sleep Modes: WSM (WiFi Sleep Mode), WDS (WiFi Deep Sleep)
- Relevant für batteriebetriebene Anwendungen

## Zusammenfassung der Beziehungen

1. **Main → All Modules**: Orchestrierung via MPLAB Harmony Task System
2. **WiFi App ↔ System WiFi Service**: Konfiguration und Event-Handling
3. **HTTP Server ↔ USB MSD**: Web-Content Bereitstellung
4. **WebSocket Server ↔ Web Browser**: Echtzeit-Kommunikation
5. **MQTT Client → Cloud**: IoT-Datenübertragung
6. **All Modules → Logger**: Debugging-Output
7. **Bootstrap Studio → WebPage → SPI Flash**: Web-Design-Pipeline
8. **Python Clients → WebSocket Server**: Test und Entwicklung
9. **Framework Dependencies**: Alle Module nutzen Harmony 3 Services

Diese Architektur ermöglicht eine flexible, erweiterbare IoT-Lösung mit moderner Web-Technologie und professionellem Embedded-Framework.
