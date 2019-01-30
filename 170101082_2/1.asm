
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

DATA SEGMENT
    a DW ?  ; Declare variable a
    d DW ?  ; Declare variable d
    n DW ?  ; Declare variable n
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
    START:
        MOV AX, DATA
        MOV DS, AX
        
        MOV a, 0000H    ; Set a to 0000H
        MOV d, 0009H    ; Set d to 0003H
        MOV n, 0006H    ; Set n to 000AH (10)
        
        MOV CX, n       ; Set CX to n, i.e. 000AH (10)
        MOV SI, 0006H   ; Set Offset to 0006H. The output starts from 0010:0006 memory location
        L1: MOV AX, a       ; Set AX to a 
            MOV [SI], AX    ; Write value of AX to memory location of SI
            ADD SI, 0002H   ; Increase offset by 2, i.e. 16 bytes
            MOV AX, a       ; Set AX to a
            ADD AX, d       ; Add d to AX
            MOV a, AX       ; Store a+d in a
            LOOP L1         ; Loop back to L1

; Output array starts from 0010:0006            

CODE ENDS

ret




