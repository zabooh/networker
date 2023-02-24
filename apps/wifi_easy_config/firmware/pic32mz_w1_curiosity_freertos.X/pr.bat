SET IPE_DIR="C:\Program Files\Microchip\MPLABX\v6.05\mplab_platform\mplab_ipe"
SET CUR_DIR="C:\Users\m91221\wolf\wireless_apps_pic32mzw1_wfi32e01\apps\wifi_easy_config\firmware\pic32mz_w1_curiosity_freertos.X" 

rem java -jar %IPE_LOC%\ipecmd.jar -TPSNAP -P32MZ1025W104132 -M -F%REL_FILE%.hex -OL -OAS2

cd %IPE_DIR%
java -jar ipecmdboost.jar -TPSNAP -P32MZ1025W104132 -M -FC:\Users\m91221\wolf\wireless_apps_pic32mzw1_wfi32e01\apps\wifi_easy_config\firmware\pic32mz_w1_curiosity_freertos.X\dist\pic32mz_w1_curiosity_freertos\production\pic32mz_w1_curiosity_freertos.X.production.hex -OL -OAS2 -OY2012
cd %CUR_DIR%
