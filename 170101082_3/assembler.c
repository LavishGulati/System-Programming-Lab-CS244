#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct instruction{
    char instr[5];
    char opcode[5];
};

char *substr(char *input, int si, int length, int n){
    char *output = (char *)(malloc(n*sizeof(char)));
    for(int i = 0; i < length; i++){
        output[i] = input[i+si];
    }
    return output;
}

struct instruction *getOpcodeArray(FILE *inputOpcodeFile){
    struct instruction *opcodeArray = (struct instruction *)malloc(12*sizeof(struct instruction));
    char s[15];     // Each line in inputOpcode.txt
    int n = 15;     // Size of each line in inputOpcode.txt
    for(int i = 0; i < 12; i++){
        fgets(s, n, inputOpcodeFile);

        if(!strcmp(substr(s, 0, 2, n), "LO")){
            strcpy(opcodeArray[i].instr, "LOOP");
        }
        else if(!strcmp(substr(s, 0, 2, n), "OR")){
            strcpy(opcodeArray[i].instr, "OR");
        }
        else{
            strcpy(opcodeArray[i].instr, substr(s, 0, 3, n));
        }

        strcpy(opcodeArray[i].opcode, substr(s, 8, 4, n));
    }

    return opcodeArray;
}

bool checkIfSubstring(char *input, int n, char *s, int m){
    for(int i = 0; i <= n-m; i++){
        if(!strcmp(substr(input, i, m, n), s)) return true;
    }
    return false;
}

void pass1(struct instruction *opcodeArray, FILE *inputFile){
    char s[1000];   // Each line in input.asm
    int n = 1000;   // Size of each line in input.asm
    bool start = false;

    FILE *fp =
    while(1){
        fgets(s, n, inputFile);
        if(!start){
            if(checkIfSubstring(s, n, "START", 5)){
                start = true;
            }
            continue;
        }

        if(checkIfSubstring(s, n, "END", 3)) break;

        // printf("%s\n", "START");

        
    }
}

int main(){
    FILE *inputFile, *inputOpcodeFile;
    inputFile = fopen("input.asm", "r");
    inputOpcodeFile = fopen("inputOpcode.txt", "r");

    struct instruction *opcodeArray = getOpcodeArray(inputOpcodeFile);

    inputOpcodeFile.close();

    pass1(opcodeArray, inputFile);

    inputFile.close();
}
