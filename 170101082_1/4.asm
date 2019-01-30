
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

MOV AX, 0002H      ; Move 0002H to AX 
PUSH AX            ; Push 0002H stored in AX to stack
MOV AX, 0003H      ; Move 0003H to AX
PUSH AX            ; Push 0003H stored in AX to stack
MOV AX, 0002H      ; Move 0002H to AX
PUSH AX            ; Push 0002H stored in AX to stack
POP AX             ; Pop 0002H stored in stack to AX
POP BX             ; Pop 0003H stored in stack to BX
MUL BX             ; Multiply 0002H and 0003H and store 0006H in AX
PUSH AX            ; Push 0006H stored in AX to stack
POP AX             ; Pop 0006H stored in stack to AX
POP BX             ; Pop 0002H stored in stack to BX
ADD AX, BX         ; Add 0002H and 0006H and store it in AX
PUSH AX            ; Push 0008H stored in AX to stack
MOV AX, 0004H      ; Move 0004H to AX
PUSH AX            ; Push 0004H stored in AX to stack
POP BX             ; Pop 0004H stored in stack to BX
POP AX             ; Pop 0008H stored in stack to AX
SUB AX, BX         ; Subtract 0008H - 0004H and store 0004H in AX
; Final result in AX

ret




