# Harmony 3 Wireless application that shows the capabilities of the WFI32

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices. Refer to the following links for more information.

-   [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)

-   [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)

-   [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)

-   [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)

-   [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)


This repository contains the MPLAB® Harmony 3 Wireless application example for PIC32MZ W1 family

![2023-04-18 10_45_32-Networker_WFI32 - PowerPoint](https://github.com/zabooh/networker/blob/master/docs/2023-04-18%2010_45_32-Networker_WFI32%20-%20PowerPoint.png)

The SPI Flash is automatically formatted with a FAT12 file system and displayed as a USB mass storage device on a connected PC as a separate hard drive.

The contents of this disk is the web page directory.
Unfortunately, write access is a bit slow at around 30 KB/secs.

Any Web Page SDK can be used to generate the content of the web page. We used Bootstrap Studio as an example here.

After the website has been loaded, a websocket connection is established from the browser to the webscket server of the WFI32.
JSON data is exchanged through this connection.

This allows the WFI32 to proactively send data to the web app for immediate operation.

After cloning the project you need also to clone the neccessary framework Repositories, if yuo want to use the Microchip Code Configurator to re-configure the project.
To make this process a bit easier, we created a batchjob (and shell script) "\networker\apps\wifi_easy_config\git_clone_h3.bat" and 
"\networker\apps\wifi_easy_config\git_clone_h3.sh", that clones and checkout all neccessary repositories. 

You should first create a directory where you clone the "networker". The above mentioned batch job will create beside this a directory "h3" that holds the frameworks. 

In "\networker\apps\wifi_easy_config\WebPage\" is the content of the Web Page that must be copied ober to the SPI Flash via USB MSD. 
   


