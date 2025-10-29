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
}block;

typedef struct header {
    long nblock;
    long nrecord;
}header;

typedef struct tof {
    FILE *f;
    header h;
}tof;

#endif