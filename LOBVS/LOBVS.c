#include "LOBVS.h" 

void lobvs_open(lobvs **f, char *name, char mode) {
    *f = malloc(sizeof(lobvs));
    if (mode == 'E'){
        (*f)->f = fopen(name, 'rb+');
        fread(&((*f)->h), sizeof(header), 1, (*f)->f);
    }
    if (mode == 'N'){
        (*f)->f = fopen(name, 'wb+');
        (*f)->h.head = -1;
        (*f)->h.newblock = -1;
        (*f)->h.freeblock = -1;
        (*f)->h.pos = 0;
    }
}

void lobvs_close(lobvs *f){
    fseek(f->f, 0, SEEK_SET);
    fwrite(&(f->h), sizeof(header), 1, f->f);  
    fclose(f->f);
    free(f);
}

void lobvs_readblock(lobvs *f,int i,block *buffer)
{
    fseek(f->f, sizeof(header) + (i - 1) * sizeof(block), SEEK_SET);
    fread(buffer, sizeof(block), 1, f->f);
}

void lobvs_writeblock(lobvs *f,int i,block *buffer)
{
    fseek(f->f, sizeof(header) + (i - 1) * sizeof(block), SEEK_SET);
    fwrite(buffer, sizeof(block), 1, f->f);
}

int get_header_lobvs(lobvs *f, int i)
{
    switch (i)
    {
        case 1: return f->h.head;
        case 2: return f->h.pos;
        case 3: return f->h.newblock;
        case 4: return f->h.freeblock;
    };
}

void set_header_lobvs(lobvs *f, int i, int value)
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