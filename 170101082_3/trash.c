if(!strcmp(command, "MOV")){
    bits += 4;
    bits += 5;
    if(val2[0] == 'R') offset += 5;
    else{
        if(strstr(val2, "H") != NULL){
            bits += 16;
        }
        // Complete for other types also like decimal
    }

    offset += ceil(bits/8.00);
}
else if(!strcmp(command, "ADD")){
    bits += 4;
    bits += 5;
    if(val2[0] == 'R') offset += 5;
    else{
        if(strstr(val2, "H") != NULL){
            bits += 16;
        }
        // Complete for other types also like decimal
    }

    offset += ceil(bits/8.00);
}
else if(!strcmp(command, "SUB")){
    bits += 4;
    bits += 5;
    if(val2[0] == 'R') offset += 5;
    else{
        if(strstr(val2, "H") != NULL){
            bits += 16;
        }
        // Complete for other types also like decimal
    }

    offset += ceil(bits/8.00);
}
else if(!strcmp(command, "MUL")){
    offset +=
}
else if(!strcmp(command, "CMP")){

}
else if(!strcmp(command, "AND")){

}
else if(!strcmp(command, "OR")){

}
else if(!strcmp(command, "NOT")){

}
else if(!strcmp(command, "JMP")){

}
else if(!strcmp(command, "LOOP")){

}
else if(!strcmp(command, "HLT")){

}
else if(!strcmp(command, "JNZ")){

}
