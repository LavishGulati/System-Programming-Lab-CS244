
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

MOV AH, 90H     ; CF = 0, SF = 0, ZF = 0 
MOV BH, 80H     ; CF = 0, SF = 0, ZF = 0
ADD AH, BH      ; CF = 1, SF = 0, ZF = 0, Adding 90H + 80H = 110H results in carry
SUB AH, BH      ; CF = 1, SF = 1, ZF = 0, Subtracting 10H - 80H = 90H results in negative value
ADD BH, 10H     ; CF = 0, SF = 1, ZF = 0, Adding 80H + 10H = 90H results in no carry
SUB AH, BH      ; CF = 0, SF = 0, ZF = 1, Subtracting 90H - 90H = 00H results in zero flag

ret




