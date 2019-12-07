//
// Created by michel on 19/11/2019.
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

#define FLOAT 1
#define INT 2
#define SUM 3
#define MINUS 4
#define MULTIPLY 5
#define DIVIDE 6
#define ATTRS 7
#define EXP 8
#define T_VARIABLE 9
#define PRINTS 10

typedef struct STRUCT{
    int typeFlag;
    void *content;
    struct TREE *left;
    struct TREE *right;
} NO;

typedef struct TREE{
    NO *root;
    struct TREE *next;
} TREE;

typedef struct treeList {
    struct TREE *first;
    struct TREE *last;
} TREELIST;

TREELIST *treeList;

void startTree(){
    treeList = (TREELIST *) malloc(sizeof(treeList));
    treeList->first = NULL;
    treeList->last = NULL;
}

void newNode(TREE *tree){
    if(treeList->first == NULL){
        treeList->first = tree;
        treeList->last = tree;
        return;
    }
    treeList->last->next = tree;
    treeList->last = tree;
}

TREE *createNodeSumInt(int first, int second){
    TREE *firstNumber = (TREE *) malloc(sizeof(firstNumber));
    firstNumber->root->typeFlag = INT;
    firstNumber->root->content = (int *)first;

    TREE *secondNumber = (TREE *) malloc(sizeof(secondNumber));
    secondNumber->root->typeFlag = INT;
    secondNumber->root->content = (int *)second;

    TREE *operation = (TREE *) malloc(sizeof(operation));
    operation->root->typeFlag = SUM;
    operation->root->left = firstNumber;
    operation->root->right = secondNumber;
    newNode(operation);
    return operation;
}

void createNodePrintInt(int *number){
    TREE *numberPrint = (TREE *) malloc(sizeof(numberPrint));
    NO *no = (NO *) malloc(sizeof(no));
    no->typeFlag = INT;
    no->content = number;
//    no->left = NULL;
//    no->right = NULL;
    numberPrint->root = no;
    numberPrint->next = NULL;

    TREE *operation = (TREE *) malloc(sizeof(operation));
    NO *no2 = (NO *) malloc(sizeof(no2));
    no2->typeFlag = PRINTS;
    no2->right = numberPrint;
//    no2->left = NULL;
//    no2->content = NULL;
    operation->root = no2;
    operation->next = NULL;
    newNode(operation);
}

void createNodePrintFloat(float *number){
    TREE *numberPrint = (TREE *) malloc(sizeof(numberPrint));
    NO *no = (NO *) malloc(sizeof(no));
    no->typeFlag = FLOAT;
    no->content = number;
    numberPrint->root = no;

    TREE *operation = (TREE *) malloc(sizeof(operation));
    NO *no2 = (NO *) malloc(sizeof(no2));
    no2->typeFlag = PRINTS;
    no2->right = numberPrint;
    operation->root = no2;
    newNode(operation);
}

void *executeNo(NO *no){
    switch (no->typeFlag){
        case INT:{
            return no->content;
        }
        case FLOAT:{
            return no->content;
        }
        case PRINTS:{
            if(no->right->root->typeFlag == INT){
                int *toPrintInt = executeNo(no->right->root);
                printf("%i\n", *((int *) toPrintInt));
                break;
            }
            if(no->right->root->typeFlag == FLOAT){
                float *toPrintFloat = executeNo(no->right->root);
                printf("%f\n", *((float *) toPrintFloat));
                break;
            }
        }
    }
}

void execute(){
    TREE *executeList = treeList->last;
    while(executeList != NULL){
        executeNo(executeList->root);
        executeList = executeList->next;
    }
}
