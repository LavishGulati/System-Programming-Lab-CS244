#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

// Number of commands
#define numInstr 12

// Instruction struct which stores an intruction and its opcode
struct instruction{
    char instr[5];
    char opcode[5];
};

// Decimal to hexadecimal converter (for registers)
char *decToHex(int n){
    char *output = (char *)(malloc(5*sizeof(char)));
    for(int i = 0; i < 4; i++){
        output[i] = '0';
    }

    int i = 3;
    while(n != 0){
        int temp = 0;
        temp = n%16;
        if(temp < 10){
            output[i] = temp+48;
            i--;
        }
        else{
            output[i] = temp+55;
            i--;
        }

        n /= 16;
    }

    output[4] = '\0';
    return output;
}

// Hexadecimal to binary converter
char *hexToBin(char *s){
    char *output = (char *)(malloc(17*sizeof(char)));
    int i;
    if(strlen(s) == 5) i = 0;
    else i = 1;

    for(int j = 0; j < 4; j++){
        if(s[i+j] == '0'){
            sprintf(output+4*j, "0000");
        }
        else if(s[i+j] == '1'){
            sprintf(output+4*j, "0001");
        }
        else if(s[i+j] == '2'){
            sprintf(output+4*j, "0010");
        }
        else if(s[i+j] == '3'){
            sprintf(output+4*j, "0011");
        }
        else if(s[i+j] == '4'){
            sprintf(output+4*j, "0100");
        }
        else if(s[i+j] == '5'){
            sprintf(output+4*j, "0101");
        }
        else if(s[i+j] == '6'){
            sprintf(output+4*j, "0110");
        }
        else if(s[i+j] == '7'){
            sprintf(output+4*j, "0111");
        }
        else if(s[i+j] == '8'){
            sprintf(output+4*j, "1000");
        }
        else if(s[i+j] == '9'){
            sprintf(output+4*j, "1001");
        }
        else if(s[i+j] == 'A'){
            sprintf(output+4*j, "1010");
        }
        else if(s[i+j] == 'B'){
            sprintf(output+4*j, "1011");
        }
        else if(s[i+j] == 'C'){
            sprintf(output+4*j, "1100");
        }
        else if(s[i+j] == 'D'){
            sprintf(output+4*j, "1101");
        }
        else if(s[i+j] == 'E'){
            sprintf(output+4*j, "1110");
        }
        else if(s[i+j] == 'F'){
            sprintf(output+4*j, "1111");
        }
    }

    output[16] = '\0';
    return output;
}

// Decimal to binary converter (for registers)
char *decToBin(int n){
    char *output = (char *)(malloc(6*sizeof(char)));
    for(int i = 0; i < 6; i++){
        output[i] = '0';
    }

    int i = 4;
    while(n != 0){
        int temp = 0;
        temp = n%2;
        output[i] = temp+48;
        i--;

        n /= 2;
    }

    output[5] = '\0';
    return output;
}

// Decimal to binary converter (for decimal immediate values)
char *decToBin2(int n){
    char *output = (char *)(malloc(17*sizeof(char)));
    for(int i = 0; i < 17; i++){
        output[i] = '0';
    }

    int i = 15;
    while(n != 0){
        int temp = 0;
        temp = n%2;
        output[i] = temp+48;
        i--;

        n /= 2;
    }

    output[16] = '\0';
    return output;
}

// Return substring of a string with given start index and length of substring
char *substr(char *input, int si, int length, int n){
    char *output = (char *)(malloc(n*sizeof(char)));
    for(int i = 0; i < length; i++){
        output[i] = input[i+si];
    }
    output[length] = '\0';
    return output;
}

// Build opcode array which stores commands and their opcodes
struct instruction *getOpcodeArray(FILE *inputOpcodeFile){
    struct instruction *opcodeArray = (struct instruction *)malloc(numInstr*sizeof(struct instruction));
    char s[15];     // Each line in inputOpcode.txt
    int n = 15;     // Size of each line in inputOpcode.txt

    // Read each line in input opcode file and store it in array
    for(int i = 0; i < numInstr; i++){
        fgets(s, n, inputOpcodeFile);

        for(int i = 0; i < strlen(s); i++){
            s[i] = toupper(s[i]);
        }

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

    // Return the array
    return opcodeArray;
}

// Writes command and its opcode to output opcode table file
void printOpcode(struct instruction *opcodeArray, bool isPrinted[numInstr], FILE *opcodeOutputFile, char *command){
    for(int i = 0; i < numInstr; i++){
        if(!strcmp(opcodeArray[i].instr, command)){
            // If not written already, write the opcode
            if(!isPrinted[i]){
                isPrinted[i] = true;
                fprintf(opcodeOutputFile, "%-5s%10s\n", command, opcodeArray[i].opcode);
            }
            break;
        }
    }
}

// Checks if a read line is blank (means it doesn't contain any intruction) or not
bool checkIfBlank(char *s, int n){
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == ';') return true;
        else if(s[i] >= 'A' && s[i] <= 'Z') return false;
        else if(s[i] >= 'a' && s[i] <= 'z') return false;
        else if(s[i] >= '0' && s[i] <= '9') return false;
    }

    return true;
}

// Reads label address during pass 2 from symTable.txt
char *readLabelAddress(char *label){
    char output[10] = "";
    FILE *symTableFile = fopen("symTable.txt", "r");
    char s[1000];
    int n = 1000;
    char *address = (char *)(malloc(10*sizeof(char)));
    address = "";
    while(fgets(s, n, symTableFile)){

        for(int i = 0; i < strlen(s); i++){
            s[i] = toupper(s[i]);
        }

        if(!strcmp(substr(s, 0, strlen(label), strlen(s)), label)){
            strcpy(output, substr(s, strlen(s)-6, 5, strlen(s)));
            address = hexToBin(output);
            return address;
        }
    }

    printf("Label not found\n");
    return address;
}

// Pass 1
void pass1(struct instruction *opcodeArray, FILE *inputFile){
    char s[1000] = "";   // Each line in input.asm
    char upper_s[1000] = "";    // Each line converted to uppercase
    int n = 1000;   // Size of each line in input.asm
    bool start = false; // Whether the program has started or not

    bool isPrinted[numInstr];   // Array to store which commands are already printed in the opcode table
    for(int i = 0; i < numInstr; i++) isPrinted[i] = false;

    int offset = 0;     // Used in address calculation

    // Opening output files for writing
    FILE *opcodeOutputFile = fopen("opTable.txt", "w");
    FILE *symTableFile = fopen("symTable.txt", "w");

    while(1){
        // Read each line
        fgets(s, n, inputFile);

        // If no intruction in the line, then skip it
        if(checkIfBlank(s, n)){
            continue;
        }

        // Convert the line to uppercase and store in upper_s
        for(int i = 0; i < strlen(s); i++){
            upper_s[i] = toupper(s[i]);
        }

        // If not started, check for "START" command
        if(!start){
            if(strstr(upper_s, "START") != NULL){
                start = true;
            }
            continue;
        }

        // If "END" command discovered, stop the program
        if(strstr(upper_s, "END") != NULL){
            break;
        }

        // Data cleaning: Removing ';' (comments)
        for(int i = 0; s[i] != '\0'; i++){
            if(s[i] == ';') s[i] = '\0';
        }

        char label[100] = "";    // 100 is the max. label size
        char command[100] = "";
        char val1[100] = "";
        char val2[100] = "";

        // If label statement
        if(strstr(s, ":") != NULL){

            // Data cleaning: Removing ',' and ':'
            for(int i = 0; i < strlen(s); i++){
                if(s[i] == ',' || s[i] == ':') s[i] = ' ';
            }

            sscanf(s, " %s %s %s %s", label, command, val1, val2);
            char *address = decToHex(offset);
            // Printing label to symTable.txt
            fprintf(symTableFile, "%s:%10sH\n", label, address);

            // If further command not present, skip the line
            if(!strcmp(command, "")) continue;

        }
        else{
            // Data cleaning: Remove ','
            for(int i = 0; i < strlen(s); i++){
                if(s[i] == ',') s[i] = ' ';
            }

            sscanf(s, " %s %s %s", command, val1, val2);
        }

        // Convert command and values to uppercase
        for(int i = 0; i < strlen(command); i++){
            command[i] = toupper(command[i]);
        }

        for(int i = 0; i < strlen(val1); i++){
            val1[i] = toupper(val1[i]);
        }

        for(int i = 0; i < strlen(val2); i++){
            val2[i] = toupper(val2[i]);
        }

        // Calculate bits used for instructions
        int bits = 4;

        // Print opcode in output file
        if(!strcmp(command, "LOOP")){
            printOpcode(opcodeArray, isPrinted, opcodeOutputFile,"LOOP");
            printOpcode(opcodeArray, isPrinted, opcodeOutputFile, "SUB");
            printOpcode(opcodeArray, isPrinted, opcodeOutputFile, "JNZ");
        }
        else printOpcode(opcodeArray, isPrinted, opcodeOutputFile, command);

        // Address calculation for various instructions
        if(!strcmp(command, "MUL")){
            bits += 5;

            if(strstr(val1, "R") == NULL) bits += 16;
            else if(strstr(val1, "R") != NULL) bits += 5;
        }
        else if(!strcmp(command, "NOT")){
            if(strstr(val1, "R") == NULL) bits += 16;
            else if(strstr(val1, "R") != NULL) bits += 5;
        }
        else if(!strcmp(command, "JMP") || !strcmp(command, "JNZ")){
            bits += 16;
        }
        else if(!strcmp(command, "LOOP")){
            bits += 21;
            offset += ceil(bits/8.00);
            bits = 20;
        }
        else{
            if(strstr(val1, "R") == NULL && strstr(val2, "R") == NULL){
                bits += 32;
            }
            else if(strstr(val1, "R") != NULL && strstr(val2, "R") == NULL){
                bits += 21;
            }
            else if(strstr(val1, "R") != NULL && strstr(val2, "R") != NULL){
                bits += 10;
            }
            else if(strstr(val1, "R") == NULL && strstr(val2, "R") != NULL){
                bits += 21;
            }
        }

        // Increase byte offset by required amount
        offset += ceil(bits/8.00);
    }

    // Close the files
    fclose(opcodeOutputFile);
    fclose(symTableFile);
}

void pass2(struct instruction *opcodeArray, FILE *inputFile){
    char s[1000] = "";   // Each line in input.asm
    char upper_s[1000] = "";
    int n = 1000;   // Size of each line in input.asm
    bool start = false;

    int offset = 0;
    FILE *outputFile = fopen("output.o", "w");
    fprintf(outputFile, "%-10s%-50s\n", "ADDRESS", "INSTRUCTION");

    while(1){
        fgets(s, n, inputFile);

        if(checkIfBlank(s, n)){
            continue;
        }

        for(int i = 0; i < strlen(s); i++){
            upper_s[i] = toupper(s[i]);
        }

        if(!start){
            if(strstr(upper_s, "START") != NULL){
                start = true;
            }
            continue;
        }

        if(strstr(upper_s, "END") != NULL){
            break;
        }

        for(int i = 0; s[i] != '\0'; i++){
            if(s[i] == ';') s[i] = '\0';
        }

        char label[100] = "";    // 10 is the max. label size
        char command[100] = "";
        char val1[100] = "";
        char val2[100] = "";

        if(strstr(s, ":") != NULL){
            for(int i = 0; i < strlen(s); i++){
                if(s[i] == ',' || s[i] == ':') s[i] = ' ';
            }

            sscanf(s, " %s %s %s %s", label, command, val1, val2);

            if(!strcmp(command, "")) continue;
        }
        else{
            for(int i = 0; i < strlen(s); i++){
                if(s[i] == ',') s[i] = ' ';
            }

            sscanf(s, " %s %s %s", command, val1, val2);
        }

        for(int i = 0; i < strlen(command); i++){
            command[i] = toupper(command[i]);
        }

        for(int i = 0; i < strlen(val1); i++){
            val1[i] = toupper(val1[i]);
        }

        for(int i = 0; i < strlen(val2); i++){
            val2[i] = toupper(val2[i]);
        }

        char *address = decToHex(offset);
        fprintf(outputFile, "%-10s", address);

        char *opcode;
        for(int i = 0; i < numInstr; i++){
            if(!strcmp(opcodeArray[i].instr, command)){
                opcode = opcodeArray[i].opcode;
                break;
            }
        }

        if(!strcmp(command, "MUL")){
            if(strstr(val1, "H") != NULL){
                char *address = hexToBin(val1);

                fprintf(outputFile, "%4s 00001 %8s %8s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17));
            }
            else if(strstr(val1, "D") != NULL){
                int val1Dec = 0;
                int helper = 1;
                for(int i = strlen(val1)-2; i >= 0; i--){
                    val1Dec += (val1[i]-'0')*helper;
                    helper *= 10;
                }
                char *address = decToBin2(val1Dec);
                fprintf(outputFile, "%4s %8s %8s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17));
            }
            else if(strstr(val1, "B") != NULL){
                char address[17];
                for(int i = 0; i < 17; i++) address[i] = '0';
                address[16] = '\0';

                int j = 15;
                for(int i = strlen(val1)-2; i >= 0; i--){
                    address[j] = val1[i];
                    j--;
                }
                fprintf(outputFile, "%4s %8s %8s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17));
            }
            else if(strstr(val1, "O") != NULL){

            }
            else if(strstr(val1, "R") != NULL){
                int val1Dec;
                if(strlen(val1) == 2) val1Dec = val1[1]-'0';
                else if(strlen(val1) == 3) val1Dec = (val1[1]-'0')*10 + (val1[2]-'0');

                char *address = decToBin(val1Dec);
                fprintf(outputFile, "%4s 00001 %5s\n", opcode, address);
            }
        }
        else if(!strcmp(command, "NOT")){
            if(strstr(val1, "H") != NULL){
                char *address = hexToBin(val1);
                fprintf(outputFile, "%4s %8s %8s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17));
            }
            else if(strstr(val1, "D") != NULL){
                int val1Dec = 0;
                int helper = 1;
                for(int i = strlen(val1)-2; i >= 0; i--){
                    val1Dec += (val1[i]-'0')*helper;
                    helper *= 10;
                }
                char *address = decToBin2(val1Dec);
                fprintf(outputFile, "%4s %8s %8s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17));
            }
            else if(strstr(val1, "B") != NULL){
                char address[17];
                for(int i = 0; i < 17; i++) address[i] = '0';
                address[16] = '\0';

                int j = 15;
                for(int i = strlen(val1)-2; i >= 0; i--){
                    address[j] = val1[i];
                    j--;
                }
                fprintf(outputFile, "%4s %8s %8s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17));
            }
            else if(strstr(val1, "O") != NULL){

            }
            else if(strstr(val1, "R") != NULL){
                int val1Dec;
                if(strlen(val1) == 2) val1Dec = val1[1]-'0';
                else if(strlen(val1) == 3) val1Dec = (val1[1]-'0')*10 + (val1[2]-'0');

                char *address = decToBin(val1Dec);
                fprintf(outputFile, "%4s %5s\n", opcode, address);
            }
        }
        else if(!strcmp(command, "JMP")){
            char *address = readLabelAddress(val1);
            fprintf(outputFile, "%4s %4s %4s %4s %4s\n", opcode, substr(address, 0, 4, 17), substr(address, 4, 4, 17), substr(address, 8, 4, 17), substr(address, 12, 4, 17));
        }
        else if(!strcmp(command, "LOOP")){
            fprintf(outputFile, "0010 11111 00000000 00000001\n");
            char *address = decToHex(offset+4);
            fprintf(outputFile, "%-10s", address);
            char *address2 = readLabelAddress(val1);
            fprintf(outputFile, "1011 %4s %4s %4s %4s\n", substr(address2, 0, 4, 17), substr(address2, 4, 4, 17), substr(address2, 8, 4, 17), substr(address2, 12, 4, 17));
        }
        else if(!strcmp(command, "JNZ")){
            char *address = readLabelAddress(val1);
            fprintf(outputFile, "%4s %4s %4s %4s %4s\n", opcode, substr(address, 0, 4, 17), substr(address, 4, 4, 17), substr(address, 8, 4, 17), substr(address, 12, 4, 17));
        }
        else if(!strcmp(command, "HLT")){
            fprintf(outputFile, "%4s\n", opcode);
        }
        else{
            if(strstr(val1, "R") == NULL && strstr(val2, "R") == NULL){
                char *address;
                char *address2;
                if(strstr(val1, "H") != NULL){
                    address = hexToBin(val1);
                }
                else if(strstr(val1, "D") != NULL){
                    int val1Dec = 0;
                    int helper = 1;
                    for(int i = strlen(val1)-2; i >= 0; i--){
                        val1Dec += (val1[i]-'0')*helper;
                        helper *= 10;
                    }
                    address = decToBin2(val1Dec);
                }
                else if(strstr(val1, "B") != NULL){
                    address = (char *)(malloc(17*sizeof(char)));
                    for(int i = 0; i < 17; i++) address[i] = '0';
                    address[16] = '\0';

                    int j = 15;
                    for(int i = strlen(val1)-2; i >= 0; i--){
                        address[j] = val1[i];
                        j--;
                    }
                }
                else if(strstr(val1, "O") != NULL){

                }

                if(strstr(val2, "H") != NULL){
                    address2 = hexToBin(val2);
                }
                else if(strstr(val2, "D") != NULL){
                    int val2Dec = 0;
                    int helper = 1;
                    for(int i = strlen(val2)-2; i >= 0; i--){
                        val2Dec += (val2[i]-'0')*helper;
                        helper *= 10;
                    }
                    address2 = decToBin2(val2Dec);
                }
                else if(strstr(val2, "B") != NULL){
                    address2 = (char *)(malloc(17*sizeof(char)));
                    for(int i = 0; i < 17; i++) address2[i] = '0';
                    address2[16] = '\0';

                    int j = 15;
                    for(int i = strlen(val2)-2; i >= 0; i--){
                        address2[j] = val2[i];
                        j--;
                    }
                }
                else if(strstr(val2, "O") != NULL){

                }

                fprintf(outputFile, "%4s %8s %8s %8s %8s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17), substr(address2, 0, 8, 17), substr(address2, 8, 8, 17));
            }
            else if(strstr(val1, "R") != NULL && strstr(val2, "R") == NULL){
                int val1Dec;
                if(strlen(val1) == 2) val1Dec = val1[1]-'0';
                else if(strlen(val1) == 3) val1Dec = (val1[1]-'0')*10 + (val1[2]-'0');

                char *address = decToBin(val1Dec);

                char *address2;
                if(strstr(val2, "H") != NULL){
                    address2 = hexToBin(val2);
                }
                else if(strstr(val2, "D") != NULL){
                    int val2Dec = 0;
                    int helper = 1;
                    for(int i = strlen(val2)-2; i >= 0; i--){
                        val2Dec += (val2[i]-'0')*helper;
                        helper *= 10;
                    }
                    // printf("%d\n", val2Dec);
                    address2 = decToBin2(val2Dec);
                }
                else if(strstr(val2, "B") != NULL){
                    address2 = (char *)(malloc(17*sizeof(char)));
                    for(int i = 0; i < 17; i++) address2[i] = '0';
                    address2[16] = '\0';

                    int j = 15;
                    for(int i = strlen(val2)-2; i >= 0; i--){
                        address2[j] = val2[i];
                        j--;
                    }
                }
                else if(strstr(val2, "O") != NULL){

                }
                fprintf(outputFile, "%4s %5s %8s %8s\n", opcode, address, substr(address2, 0, 8, 17), substr(address2, 8, 8, 17));
            }
            else if(strstr(val1, "R") != NULL && strstr(val2, "R") != NULL){
                int val1Dec;
                if(strlen(val1) == 2) val1Dec = val1[1]-'0';
                else if(strlen(val1) == 3) val1Dec = (val1[1]-'0')*10 + (val1[2]-'0');

                char *address = decToBin(val1Dec);

                int val2Dec;
                if(strlen(val2) == 2) val2Dec = val2[1]-'0';
                else if(strlen(val2) == 3) val2Dec = (val2[1]-'0')*10 + (val2[2]-'0');

                char *address2 = decToBin(val2Dec);

                fprintf(outputFile, "%4s %5s %5s\n", opcode, address, address2);
            }
            else if(strstr(val1, "R") == NULL && strstr(val2, "R") != NULL){
                char *address;
                if(strstr(val1, "H") != NULL){
                    address = hexToBin(val1);
                }
                else if(strstr(val1, "D") != NULL){
                    int val1Dec = 0;
                    int helper = 1;
                    for(int i = strlen(val1)-2; i >= 0; i--){
                        val1Dec += (val1[i]-'0')*helper;
                        helper *= 10;
                    }
                    address = decToBin2(val1Dec);
                }
                else if(strstr(val1, "B") != NULL){
                    address = (char *)(malloc(17*sizeof(char)));
                    for(int i = 0; i < 17; i++) address[i] = '0';
                    address[16] = '\0';

                    int j = 15;
                    for(int i = strlen(val1)-2; i >= 0; i--){
                        address[j] = val1[i];
                        j--;
                    }
                }
                else if(strstr(val1, "O") != NULL){

                }

                int val2Dec;
                if(strlen(val2) == 2) val2Dec = val2[1]-'0';
                else if(strlen(val2) == 3) val2Dec = (val2[1]-'0')*10 + (val2[2]-'0');

                char *address2 = decToBin(val2Dec);
                fprintf(outputFile, "%4s %8s %8s %5s\n", opcode, substr(address, 0, 8, 17), substr(address, 8, 8, 17), address2);
            }
        }

        int bits = 4;

        if(!strcmp(command, "MUL")){
            bits += 5;

            if(strstr(val1, "R") == NULL) bits += 16;
            else if(strstr(val1, "R") != NULL) bits += 5;
        }
        else if(!strcmp(command, "NOT")){
            if(strstr(val1, "R") == NULL) bits += 16;
            else if(strstr(val1, "R") != NULL) bits += 5;
        }
        else if(!strcmp(command, "JMP") || !strcmp(command, "JNZ")){
            bits += 16;
        }
        else if(!strcmp(command, "LOOP")){
            bits += 21;     // SUB R31 0001H
            offset += ceil(bits/8.00);
            bits = 20;      // JMP Label
        }
        else{
            if(strstr(val1, "R") == NULL && strstr(val2, "R") == NULL){
                bits += 32;
            }
            else if(strstr(val1, "R") != NULL && strstr(val2, "R") == NULL){
                bits += 21;
            }
            else if(strstr(val1, "R") != NULL && strstr(val2, "R") != NULL){
                bits += 10;
            }
            else if(strstr(val1, "R") == NULL && strstr(val2, "R") != NULL){
                bits += 21;
            }
        }

        offset += ceil(bits/8.00);
    }

    fclose(outputFile);
}

int main(){

    // File pointers for input.asm and opcode table file
    FILE *inputFile, *inputOpcodeFile;

    // Make an array to store all commands and their opcodes
    inputOpcodeFile = fopen("inputOpcode.txt", "r");
    struct instruction *opcodeArray = getOpcodeArray(inputOpcodeFile);
    fclose(inputOpcodeFile);

    // Pass 1
    inputFile = fopen("input.asm", "r");
    pass1(opcodeArray, inputFile);
    fclose(inputFile);

    // Pass 2
    inputFile = fopen("input.asm", "r");
    pass2(opcodeArray, inputFile);
    fclose(inputFile);
}
