SET REL_FILE=.\dist\pic32mz_w1_curiosity_freertos\debug\pic32mz_w1_curiosity_freertos.X.debug
SET TOOL="C:\Program Files\Microchip\xc32\v3.01\bin"

%TOOL%\xc32-readelf -s %REL_FILE%.elf > %REL_FILE%.sym
cmsort /S=7,100  %REL_FILE%.sym %REL_FILE%.symbols.txt
DEL %REL_FILE%.sym   
COPY %REL_FILE%.symbols.txt .
%TOOL%\xc32-objdump -S %REL_FILE%.elf > %REL_FILE%.disassembly.txt
COPY %REL_FILE%.disassembly.txt .
COPY %REL_FILE%.map .


