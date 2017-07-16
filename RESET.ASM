; RESET.ASM
; 11/10/1989
; Reset video and keyboard.

.8086
.MODEL TINY

.DATA

data_1			EQU		49h

.CODE

		ORG	100h

main			PROC	NEAR

start:
				mov		ax,8005h
				int		10h						; Non-standard interrupt

				mov		ax,80FFh
				int		10h						; Non-standard interrupt

				mov		ax,80FFh
				int		16h						; Non-standard interrupt

				mov		ax,40h
				mov		ds,ax
				cmp		BYTE PTR DS:data_1,7
				je		loc_1					; Jump if equal

				mov		ax,3
				int		10h						; Video display
												; ah=00h, al=03h
												; Set display mode to mode 03h (text 80x25 16 color)

loc_1:
				int		20h						; DOS program terminate

main			ENDP

				END		start
