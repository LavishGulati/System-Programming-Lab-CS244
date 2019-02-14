#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct instruction{
    char instr[5];
    char opcode[5];
};

int main(){
    FILE *inputFile, *inputOpcodeFile;
    inputFile = fopen("input.asm", "r");
    inputOpcodeFile = fopen("inputOpcode.txt", "r");

    struct instruction *opcodeArray = (struct instruction *)malloc(12*sizeof(struct instruction));
    char s[15];
    for(int i = 0; i < 12; i++){
        fgets(s, 15, inputOpcodeFile);
        
    }
}
