#include "LOF.h"

void lof_open( lof **f, char *name, char mode ){
    *f = malloc( sizeof(lof) );
    if (mode == 'E'){
        (*f)->f = fopen(name, "rb+");
        fread(&((*f)->h), sizeof(header), 1, (*f)->f);
    }
    if (mode == 'N'){
        (*f)->f = fopen(name, "wb+");
        (*f)->h.head = -1;
        (*f)->h.newblock = -1;
        (*f)->h.freeblock = -1;
        (*f)->h.pos = 0;
    }
}; 

void lof_close(lof *f){
    fseek(f->f, 0, SEEK_SET);
    fwrite(&(f->h), sizeof(header), 1, f->f);  
    fclose(f->f);
    free(f);
};

void read_bloc_lof(lof *f,int i,block *buf)
{
    fseek((*f).f,i*sizeof(*buf)+sizeof(header),SEEK_SET);
    fread(buf,sizeof(*buf),1,(*f).f);
}

void write_bloc_lof(lof *f,int i,block *buf)
{
    fseek((*f).f,i*sizeof(*buf)+sizeof(block),SEEK_SET);
    fwrite(buf,sizeof(*buf),1,(*f).f);
}

int get_header_lof(lof *f, int i)
{
    switch (i)
    {
        case 1: return f->h.head;
        case 2: return f->h.pos;
        case 3: return f->h.newblock;
        case 4: return f->h.freeblock;
    };
}

void set_header_lof(lof *f, int i, int value)
{
    switch (i)
    {
        case 1: f->h.head = value;
                break;
        case 2: f->h.pos = value;
                break;
        case 3: f->h.newblock = value;
                break;
        case 4: f->h.freeblock = value;
                break;
    };
}