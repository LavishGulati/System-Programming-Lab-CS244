
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
DATA SEGMENT
    a DW ?  ; Declare variable a
DATA ENDS

CODE SEGMENT
    ASSUME CS: CODE, DS:DATA
    START:
        MOV AX, DATA
        MOV DS, AX
        
        MOV a, 07H  ; Store 03H in variable a
        
        MOV CX, a   ; Set CL to a, i.e. 03H
        MOV AX, 01H ; Set AL to 01H
        L1: MUL CX  ; Multiply AL and CL and store result in AL
            LOOP L1 ; Loop L1 and decrement CL
            
        ; Final result in AL
        
CODE ENDS        

ret




