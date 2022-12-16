; CODEIBM.ASM
; 28/02/1990
; Set the iRC Monochrome/Graphic Card (Thai Standard) to default font.

.8086
.MODEL TINY

.DATA

.CODE

        ORG 100h

main            PROC    NEAR

start:
                mov     dx,3BAh                 ; Port 3BAh
                mov     al,0                    ; Set the Thai card to default font
                out     dx,al

                int     20h                     ; DOS program terminate

main            ENDP

                END     start
