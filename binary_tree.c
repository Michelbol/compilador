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

typedef struct NO{
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
    TREE *first;
    TREE *last;
} TREELIST;

TREELIST *treeList;

void startTree(){
    treeList = (TREELIST *) malloc(sizeof(&treeList));
    treeList->first = NULL;
    treeList->last = NULL;
}

void newNode(struct TREE *tree){
    TREE *addTree = (TREE *) malloc(sizeof(&addTree));
    *addTree = *tree;
    if(treeList->first == NULL){
        treeList->first = addTree;
        treeList->last = addTree;
        return;
    }
    treeList->last->next = addTree;
    treeList->last = addTree;
}

TREE *createNodeInt(const int *number){
    TREE *numberTree = (TREE *) malloc(sizeof(&numberTree));
    NO *root = (NO *) malloc(sizeof(&root));
    int *value = (int *) malloc(sizeof(value));
    *value = *number;
    numberTree->root = root;
    numberTree->root->content = value;
    numberTree->root->typeFlag = INT;
    return numberTree;
}
TREE *createNodeFloat(const float *number){
    TREE *numberTree = (TREE *) malloc(sizeof(&numberTree));
    NO *root = (NO *) malloc(sizeof(&root));
    float *value = (float *) malloc(sizeof(value));
    *value = *number;
    numberTree->root = root;
    numberTree->root->content = value;
    numberTree->root->typeFlag = FLOAT;
    return numberTree;
}

TREE *createNodeSumInt(struct TREE *first, struct TREE *second){
    TREE *firstNumber = (TREE *) malloc(sizeof(&firstNumber));
    TREE *secondNumber = (TREE *) malloc(sizeof(&secondNumber));
    TREE *operation = (TREE * ) malloc(sizeof(&operation));
    firstNumber = first;
    secondNumber = second;
    operation->root->typeFlag = SUM;
    operation->root->right = firstNumber;
    operation->root->left = secondNumber;
    newNode(operation);
}

void createNodePrintInt(struct TREE *numberPrint){
    TREE *operation = (TREE *) malloc(sizeof(&operation));
    NO *no2 = (NO *) malloc(sizeof(&no2));
    TREE *number = (TREE * ) malloc(sizeof(&numberPrint));
    *number = *numberPrint;
    no2->typeFlag = PRINTS;
    no2->right = number;
    operation->root = no2;
    operation->next = NULL;
    newNode(operation);
}
void createNodePrintFloat(struct TREE *numberPrint){
    TREE *operation = (TREE *) malloc(sizeof(&operation));
    NO *no2 = (NO *) malloc(sizeof(&no2));
    TREE *number = (TREE * ) malloc(sizeof(&numberPrint));
    *number = *numberPrint;
    no2->typeFlag = PRINTS;
    no2->right = number;
    operation->root = no2;
    operation->next = NULL;
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
        case SUM:
            printf("é uma soma");
            break;
    }
}

void execute(){
    TREE *executeList = treeList->first;
    while(executeList != NULL){
        executeNo(executeList->root);
        executeList = executeList->next;
    }
}
