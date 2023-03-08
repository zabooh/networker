set H3_INSTALL=../../../h3
set H3_GITHUB="https://github.com/Microchip-MPLAB-Harmony"

git clone -b "v3.15.0"              %H3_GITHUB%/bsp.git %H3_INSTALL%/bsp
git clone -b "v10.4.6"              %H3_GITHUB%/CMSIS-FreeRTOS.git %H3_INSTALL%/CMSIS-FreeRTOS
git clone -b "v3.11.1"              %H3_GITHUB%/core.git %H3_INSTALL%/core
git clone -b "v3.14.0"              %H3_GITHUB%/csp.git  %H3_INSTALL%/csp
git clone -b "v3.7.0"               %H3_GITHUB%/wireless_wifi.git %H3_INSTALL%/wireless_wifi
git clone -b "v3.11.0-E1"           %H3_GITHUB%/usb.git %H3_INSTALL%/usb
git clone -b "v3.13.1"              %H3_GITHUB%/dev_packs.git %H3_INSTALL%/dev_packs
git clone -b "v3.7.0"               %H3_GITHUB%/wireless_system_pic32mzw1_wfi32e01.git %H3_INSTALL%/wireless_system_pic32mzw1_wfi32e01
git clone -b "v4.7.0"               %H3_GITHUB%/wolfssl.git %H3_INSTALL%/wolfssl
git clone -b "v3.8.0"               %H3_GITHUB%/net.git %H3_INSTALL%/net
git clone -b "v3.7.6"               %H3_GITHUB%/crypto.git %H3_INSTALL%/crypto
git clone -b "v3.8.5"               %H3_GITHUB%/mhc.git %H3_INSTALL%/mhc
