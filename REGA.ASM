; REGA.ASM
; 07/01/1991
; Add Thai font to screen font, KU code.

.8086
.MODEL TINY

.DATA

include "rega.inc"

.CODE

		ORG	100h

main			PROC	NEAR

start:
				push	ds
				pop		es						; Make sure ES = DS

				mov		ax,1101h
				xor		bx,bx					; Clear bx
				inc		bl						; Load 1 block
				int		10h						; Video display
												; ah=11h, al=04h
												; Load ROM 8x14 character set
												; bl=01h

				mov		ax,OFFSET Font			; Offset to font data
				mov		bp,ax
				mov		ax,1100h
				mov		bh,0Eh					; 14 points
				xor		bl,bl					; Clear bl, load 0 block
				mov		cx,80h					; Load 128 characters
				mov		dx,80h					; Character offset 80h
				int		10h						; Video display
												; ah=11h, al=00h
												; Load user-specified patterns
												; bh=10h, bl=00h
												; cx=80h, dx=80h

				int		20h						; DOS program terminate

main			ENDP

				END		start
