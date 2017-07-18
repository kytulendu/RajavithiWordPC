; RORG.ASM
; 17/09/1991
; Reset the EGA/VGA screen font to original.

.8086
.MODEL TINY

.CODE

		ORG	100h

main			PROC	NEAR

start:
				xor		ax,ax					; Clear ax
				mov		al,12h
				int		10h						; Video display
												; ah=00h, al=12h
												; Set display mode to mode 12h (graphic 640x480 16 color)

				xor		ax,ax					; Clear ax
				mov		al,3
				int		10h						; Video display
												; ah=00h, al=03h
												; Set display mode to mode 03h (text 80x25 16 color)

				int		20h						; DOS program terminate

main			ENDP

				END		start
