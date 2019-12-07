#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include "helpers.c"
#define TRUE 1
#define FALSE 0
#define IVAL 0
#define FVAL 1


typedef struct variables {
    char *key;
    int intVal;
    float floatVal;
    int type;
    struct variables *next;
} VARIABLE;

typedef struct variablesList {
    struct variables *first;
    struct variables *last;
} LIST;

LIST *variables;

void startList(){
    variables = (LIST *) malloc(sizeof(variables));
    variables->first = NULL;
    variables->last = NULL;
}

VARIABLE *findVariable(VARIABLE *variable, char *key){
    if(!variable){
        return NULL;
    }
    if(strcmp(variable->key,key) == 0){
        return variable;
    }
    VARIABLE *variableAux = findVariable(variable->next, key);
    if(variableAux){
        return variableAux;
    }
    return findVariable(variable->next, key);
}

VARIABLE *findVariableList(char *key){
    return findVariable(variables->first, key);
}

VARIABLE *insertVariable(char *key, int ival){
    if(variables->first == NULL || variables->last == NULL){
        variables->first = (VARIABLE*)malloc(sizeof(VARIABLE));
        variables->first->key = key;
        variables->first->next = NULL;
        variables->first->intVal = ival;
        variables->last = variables->first;
        return variables->first;
    }
    VARIABLE *variable = findVariable(variables->first, key);
    if(variable != NULL){
        variable->intVal = ival;
        variable->type = IVAL;
        return variable;
    }
    VARIABLE *aux = (VARIABLE*)malloc(sizeof(VARIABLE));
    aux->key = key;
    aux->next = NULL;
    aux->intVal = ival;
    aux->type = IVAL;
    variables->last->next = aux;
    variables->last = aux;
    return variables->last;
}

VARIABLE *insertVariableF(char *key, float fval){
    if(variables->first == NULL || variables->last == NULL){
        variables->first = (VARIABLE*)malloc(sizeof(VARIABLE));
        variables->first->key = key;
        variables->first->next = NULL;
        variables->first->floatVal = fval;
        variables->first->type = FVAL;
        variables->last = variables->first;
        return variables->first;
    }
    VARIABLE *variable = findVariable(variables->first, key);
    if(variable != NULL){
        variable->floatVal = fval;
        variable->type = FVAL;
        return variable;
    }
    VARIABLE *aux = (VARIABLE*)malloc(sizeof(VARIABLE));
    aux->key = key;
    aux->next = NULL;
    aux->floatVal = fval;
    aux->type = FVAL;
    variables->last->next = aux;
    variables->last = aux;
    return variables->last;
}

void printVariable(VARIABLE *variable){
    printf("[");
    printf("Nome: %s - ", variable->key);
    if(variable->intVal >= 0){
        printf("Valor: %i", variable->intVal);
    }else if(variable->floatVal >= 0){
        printf("Valor: %f", variable->floatVal);
    }
    printf("]\n");
}

void printList(VARIABLE *variable){
    if(variable){
        printVariable(variable);
        printList(variable->next);
    }
}

VARIABLE *findAndPrintVariable(char *key){
    VARIABLE *variable = findVariable(variables->first, key);
    if(variable == NULL){
        return NULL;
    }
    return variable;
}