; RVGA.ASM
; 08/01/1991
; Add Thai font to screen font, KU code.

.8086
.MODEL TINY

.DATA

include "rvga.inc"

.CODE

		ORG	100h

main			PROC	NEAR

start:
				push	ds
				pop		es						; Make sure ES = DS

				mov		ax,1104h
				xor		bx,bx					; Clear bx
				inc		bl						; Load 1 block
				int		10h						; Video display
												; ah=11h, al=04h
												; Load ROM 8x16 character set
												; bl=01h

				mov		ax,OFFSET Font			; Offset to font data
				mov		bp,ax
				mov		ax,1100h
				mov		bh,10h					; 16 points
				xor		bl,bl					; Clear bl, load 0 block
				mov		cx,80h					; Load 128 characters
				mov		dx,80h					; Character offset 80h
				int		10h						; Video display
												; ah=11h, al=00h
												; Load user-specified patterns
												; bh=10h, bl=00h
												; cx=80h, dx=80h

				mov		ah,4Ch
				int		21h						; Exit with return code in al

main			ENDP

				END		start
