; THAICOUR.ASM
; 16/12/2022
; Change VGA screen font to Thai Courier, KU code.

.8086
.MODEL TINY

.DATA

include "thaicour.inc"

.CODE

        ORG 100h

main            PROC    NEAR

start:
                push    ds
                pop     es                      ; Make sure ES = DS

                mov     ax,1104h
                xor     bx,bx                   ; Clear bx
                inc     bl                      ; Load 1 block
                int     10h                     ; Video display
                                                ; ah=11h, al=04h
                                                ; Load ROM 8x16 character set
                                                ; bl=01h

                mov     ax,OFFSET Font          ; Offset to font data
                mov     bp,ax
                mov     ax,1100h
                mov     bh,10h                  ; 16 points
                xor     bl,bl                   ; Clear bl, load 0 block
                mov     cx,0ffh                 ; Load 256 characters
                mov     dx,00h                  ; Character offset 00h
                int     10h                     ; Video display
                                                ; ah=11h, al=00h
                                                ; Load user-specified patterns
                                                ; bh=10h, bl=00h
                                                ; cx=ffh, dx=00h

                int     20h                     ; DOS program terminate

main            ENDP

                END     start
