@ECHO OFF
REM BIN2INC UTILITY
wcl bin2inc.c

REM RESET.COM
wasm reset
wlink name reset format dos com file reset.obj

REM RORG.COM
wasm rorg
wlink name rorg format dos com file rorg.obj

REM REGA.COM
bin2inc rega.fon rega.inc
wasm rega
wlink name rega format dos com file rega.obj

REM RVGA.COM
bin2inc rvga.fon rvga.inc
wasm rvga
wlink name rvga format dos com file rvga.obj

REM THAICOUR.COM
bin2inc thaicour.fon thaicour.inc
wasm thaicour
wlink name thaicour format dos com file thaicour.obj

REM CODEKU.COM
wasm codeku
wlink name codeku format dos com file codeku.obj

REM CODEIBM.COM
wasm codeibm
wlink name codeibm format dos com file codeibm.obj

REM RW.EXE
wcl rw.c
