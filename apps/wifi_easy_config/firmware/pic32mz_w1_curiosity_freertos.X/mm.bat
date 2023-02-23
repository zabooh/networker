SET REL_FILE=.\dist\pic32mz_w1_curiosity_freertos\production\pic32mz_w1_curiosity_freertos.X.production
SET TOOL="C:\Program Files\Microchip\xc32\v3.01\bin"
SET GNU_BIN="C:\Program Files\Microchip\MPLABX\v6.05\gnuBins\GnuWin32\bin\"

@echo BEL

%GNU_BIN%\make -j6

echo ^G