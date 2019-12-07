//
// Created by michel on 26/11/2019.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define TRUE 1
#define FALSE 0

double convertCommaValueToFloat(char* number){
    char newNumber[strlen(number)];
    int sizeNumber = 0;
    for (int i = 0; i < strlen(number); i++){
        if(isdigit(number[i]) != FALSE){
            newNumber[sizeNumber] = number[i];
            sizeNumber = sizeNumber+1;
        }else if(number[i] == ','){
            newNumber[sizeNumber] = '.';
            sizeNumber = sizeNumber+1;
        }else if(number[i] == '-' && sizeNumber == 0){
            newNumber[sizeNumber] = '-';
            sizeNumber = sizeNumber+1;
        }
    }
    return atof(newNumber);
}


int isInt(char *value){
    int sizeValue = strlen(value);
    for (int i = 0; i < sizeValue; i++){
        if(isdigit(value[i]) == FALSE){
            return FALSE;
        }
    }
    return TRUE;
}

int isFloat(char *value){
    int sizeValue = strlen(value);
    int hasDot = FALSE;
    for (int i = 0; i < sizeValue; i++){
        if(value[i] == '.'){
            hasDot = TRUE;
        }
        if(isdigit(value[i]) == FALSE && value[i] != '.'){
            return FALSE;
        }
    }
    return hasDot;
}