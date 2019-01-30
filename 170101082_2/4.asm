
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

MOV AX, 0A4C3H   ; Set AX to 016AH, i.e. the number you want to reverse
MOV BH, AL       ; Set BH to AL
ROL BH, 4        ; Rotate BH by 4 bits to left, i.e. reverse the 8-byte number
MOV BL, AH       ; Set BL to AH
ROL BL, 4        ; Rotate BH by 4 bits to left, i.e. reverse the 8-byte number

; Final result in BX


; Reverse in binary format
; If you wanna check this code, comment the rotation lines above
; i.e. Comment the lines ROL BH, 4 and ROL BL, 4
; and uncomment the below piece of code by removing COMMENT @ at the start of code and @ at the end of code

COMMENT @

MOV CL, 8 
L1: ROL BH, 1   

    JC L2
    
    L5:
    
    JNC L3
     
    L6:
    
    LOOP L1

JMP L7

L2: PUSH 01H
    JMP L5
    
L3: PUSH 00H
    JMP L6

L7:
MOV CL, 8
MOV BH, 00H    
L4: POP DX
    SHL BH, 1
    ADD BH, DL
    LOOP L4
    
MOV CL, 8 
L8: ROL BL, 1   

    JC L9
    
    L11:
    
    JNC L10
     
    L12:
    
    LOOP L8

JMP L13
 
L9: PUSH 01H
    JMP L11
    
L10: PUSH 00H
    JMP L12

L13:
MOV CL, 8
MOV BL, 00H    
L14: POP DX
    SHL BL, 1
    ADD BL, DL
    LOOP L14
    
; Final result in BX
  
@

ret




