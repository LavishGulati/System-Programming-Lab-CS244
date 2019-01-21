
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

MOV [0000H], 50H   ; Move 50H to [0000H]
MOV [0001H], 60H   ; Move 60H to [0001H]
MOV AL, [0000H]    ; Move 50H stored in [0000H] to AX
MOV BL, [0001H]    ; Move 60H stored in [0001H] to BX
MOV [0000H], BL    ; Move 60H stored in BX to [0000H]
MOV [0001H], AL    ; Move 50H stored in AX to [0001H]

ret




