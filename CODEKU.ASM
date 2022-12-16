; CODEKU.ASM
; 08/03/1988
; Set the iRC Monochrome/Graphic Card (Thai Standard) font to KU code.

.8086
.MODEL TINY

.DATA

.CODE

        ORG 100h

main            PROC    NEAR

start:
                mov     dx,3BAh                 ; Port 3BAh
                mov     al,2                    ; Set the Thai card to KU font
                out     dx,al

                int     20h                     ; DOS program terminate

main            ENDP

                END     start
