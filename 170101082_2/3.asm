
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

DATA SEGMENT
DATA ENDS
    

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
    START:
        MOV AX, DATA
        MOV DS, AX
                     
        ; Storing input array to memory location starting from 0010:0000
        MOV [SI], 04H
        INC SI          ; Increment SI to point to next memory location
        MOV [SI], 02H
        INC SI
        MOV [SI], 02H
        INC SI
        MOV [SI], 04H
        INC SI
        MOV [SI], 05H
        INC SI
        MOV [SI], 05H
        
        MOV SI, 0000H   ; Reset offset to 0000H so that it points to 0010:0000, i.e. the start of the input array
        MOV AL, 00H     ; Set AL to 00H
        MOV CL, 06H     ; Set CL to 05H, i.e. the number of elements in the array
        L1: XOR AL, [SI]    ; Take XOR of AL and value stored at memory location determined by offset SI
            INC SI          ; Increment SI to point to next memory location
            LOOP L1         ; Loop back and decrement CL
             
        
CODE ENDS


ret




