#ifndef LOBVS_H
#define LOBVS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct block {
    char tab[100];
    int next;
}block;

typedef struct header {
    int head; 
    int pos;
    int newblock;
    int freeblock;
}header;

typedef struct lobvs {
    FILE *f;
    header h;
} lobvs;

#endif