
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

MOV [0000H], 50H    ; Move 50H to [0000H]
MOV [0001H], 20H    ; Move 20H to [0001H]
MOV AL, [0000H]     ; Move 50H stored in [0000H] to AX
ADD AL, [0001H]     ; Add 20H stored in [0001H] to AX
MOV [0002H], AL     ; Move 70H stored in AX to [0002H]

ret




