#ifndef TOF_H
#define TOF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct record {
    long int key;
}record;

typedef struct block {
    record tab[10];
    int nrecord;
    int next;
}block;

typedef struct header {
    int head; 
    int pos;
    int newblock;
    int freeblock;
}header;

typedef struct lof {
    FILE *f;
    header h;
}lof;

#endif