SET REL_FILE=.\dist\pic32mz_w1_curiosity_freertos\production\pic32mz_w1_curiosity_freertos.X.production
SET TOOL="C:\Program Files\Microchip\xc32\v3.01\bin"
SET GNU_BIN="C:\Program Files\Microchip\MPLABX\v6.05\gnuBins\GnuWin32\bin\"
SET IPE_LOC="C:\Program Files\Microchip\MPLABX\v6.05\mplab_platform\mplab_ipe"

java -jar %IPE_LOC%\ipecmd.jar -TPSNAP -P32MZ1025W104132 -M -F%REL_FILE%.hex -OL -OAS2


