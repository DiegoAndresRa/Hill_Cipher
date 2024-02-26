#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Utilities.h"
int main(int argc, char* argv[]){
    char mode;
    char* key = (char*)malloc(100*sizeof(char));
    char* message = (char*)malloc(100*sizeof(char));

    scanf("%c",&mode);
    fpurge(stdin);

    scanf("%[^\n]s",key);
    fpurge(stdin);
    int** key_matrix = matrixKey(key);

    fpurge(stdin);
    scanf("%[^\n]s",message);
    int** mes_matrix = matrixMessage(message,key);

    free(key);
    free(message);
    
    
}