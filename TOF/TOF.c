#include "TOF.h"

void tof_open( tof **f , char *name , char mode ){
    *f = malloc( sizeof(tof) );
    if (mode == 'E'){
        (*f)->f = fopen(name, "rb+");
        fread(&((*f)->h), sizeof(header), 1, (*f)->f);

    }
    if (mode == 'N'){
        (*f)->f = fopen(name, "wb+");
        (*f)->h.nblock = 0;
        (*f)->h.nrecord = 0;
        fwrite(&((*f)->h), sizeof(header), 1, (*f)->f);
    }
};

void tof_close(tof *f){
    fseek(f->f, 0, SEEK_SET);
    fwrite(&(f->h), sizeof(header), 1, f->f);  
    fclose(f->f);
    free(f);
};

void tof_readblock(tof *f, long i, block *buffer ){
    fseek(f->f, sizeof(header) + (i - 1) * sizeof(block), SEEK_SET);
    fread(buffer, sizeof(block), 1, f->f);
};

void tof_writeblock(tof *f, long i, block *buffer){
    fseek(f->f, sizeof(header) + (i - 1) * sizeof(block), SEEK_SET);
    fwrite(buffer, sizeof(block), 1, f->f);
};

long get_header(tof *f, int i){
    switch (i) {
        case 1 : {
            return (f->h.nblock);
            break;
        }
        case 2 : {
            return(f->h.nrecord);
            break;
        }
    }
};

void set_header(tof *f, int i, long value){
    switch (i) {
        case 1 : {
            f->h.nblock = value;
            break;
        }
        case 2 : {
            f->h.nrecord = value;
            break;
        }
    }
};

int search(tof *f, int key, int *i, int *j){
    block myblock;
    int nfirstblock = 1;
    int nlastblock = f->h.nblock;
    int found = 0;
    int key1;
    int key2;
    while (!found && nfirstblock <= nlastblock){
        *i = (nlastblock + nfirstblock) / 2;
        tof_readblock(f, *i, &myblock);
        key1 = myblock.tab[0].key;
        key2 = myblock.tab[myblock.nrecord - 1].key;
        if (key < key1){
            nlastblock =  *i - 1;
        }
        else {
            if (key > key2){
                nfirstblock = *i + 1;
            }
            else {
                found = 1;
            }
        }
    };
    int up, down;
    if (found) {
        found = 0; 
        up = 0;
        down = myblock.nrecord - 1;
        while (!found && up <= down){
            *j = (up + down) / 2;
            if (key < myblock.tab[*j].key){
                down = *j - 1;
            }
            else {
                if (key > myblock.tab[*j].key){
                    up = *j + 1;
                }
                else {
                    found = 1;
                }
            }
        }
    }
    return found;
};