#include "TOF.h"

void tof_open( tof **f , char *name , char mode){
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

int main(){
    tof * f; 
    tof_open(&f, "random", 'E');
    int nblock = f->h.nblock;
    block myblock;
    for (int i = 0; i < nblock ; i++){
        tof_readblock(f, i + 1, &myblock);
        int nrecord = myblock.nrecord;
        for (int j = 0; j < nrecord ; j++){
            printf("%d \n", myblock.tab[j].key );
        }
    }
    tof_close(f);
}