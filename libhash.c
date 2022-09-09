#include "libhash.h"
#include <stdlib.h>
#include <stdio.h>

hash_t *create_hash_table()
{
    hash_t *t;

    if (!(t = malloc(sizeof(hash_t))))
        return NULL;

    t->tam = H_TAM;
    for (int i=0; i < t->tam; i++) {
        t->keys[i].value = 0;
        t->keys[i].isValid = 0;
    }

    return t;
}

hash_t *exclude_hash_table(hash_t *t)
{
    free(t);

    return NULL;
}

int h1(int k, int m)
{
    return k % m;
}

int h2(int k, int m)
{
    return m * (k * 0.9f - (int)(k * 0.9f));
}

int include_key(hash_t *t1, hash_t *t2, int k)
{
    int i, j;
    int k_temp;

    i = h1(k, t1->tam);
    if (t1->keys[i].isValid == 0)
    {
        t1->keys[i].value = k;
        t1->keys[i].isValid = 1;

        return 1;
    }
    
    if (t1->keys[i].value != k)
    {

        k_temp = t1->keys[i].value;

        t1->keys[i].value = k;
        t1->keys[i].isValid = 1;

        j = h2(k_temp, t2->tam);

        if (t2->keys[j].isValid)
        {
            return -1;
        }

        t2->keys[j].value = k_temp;
        t2->keys[j].isValid = 1;
        
        return 2;
    }

    return 0;
}

int search_key(hash_t *t1, hash_t *t2, int k)
{
    int i;
    
    i = h1(k, t1->tam);

    if(!t1->keys[i].isValid || t1->keys[i].value != k)
    {
        i = h2(k, t2->tam);

        if(!t2->keys[i].isValid || t2->keys[i].value != k)
            return -1;

        return i + t1->tam;
    }

    return i;
}

int remove_key(hash_t *t1, hash_t *t2, int k)
{
    int i;
    
    i = search_key(t1, t2, k);

    if(i == -1)
        return 0;

    if (i < t1->tam) 
    {
        t1->keys[i].isValid = 0;
        t1->keys[i].value = 0;
        
        return 1;
    }

    i -= t1->tam;
    t2->keys[i].isValid = 0;
    t2->keys[i].value = 0;

    return 2;
}

int cmpfunc(const void *a, const void *b)
{
    int k_cmp, t_cmp, p_cmp;

    k_cmp = ((print_t*)a)->key - ((print_t*)b)->key;
    t_cmp = ((print_t*)a)->tbl - ((print_t*)b)->tbl;
    p_cmp = ((print_t*)a)->pos - ((print_t*)b)->pos;

    if (k_cmp != 0)
        return k_cmp;
    
    if (t_cmp != 0)
        return t_cmp;

    return p_cmp;
}

void print_table(hash_t *t1, hash_t *t2)
{
    print_t ord[2*H_TAM]; // vetor auxiliar para ordenar os elementos
    int tam, k;
    
    // tamanho do vetor auxilar - atualizado a cada insercao
    tam = 0; 

    // alimenta o vetor auxiliar com os dados validos das tabelas hash
    for (k = 0; k < H_TAM; k++)
    {
        if (t1->keys[k].isValid)
        {
            ord[tam].key = t1->keys[k].value;
            ord[tam].tbl = 1;
            ord[tam].pos = k;
            tam++;
        }
        if (t2->keys[k].isValid)
        {
            ord[tam].key = t2->keys[k].value;
            ord[tam].tbl = 2;
            ord[tam].pos = k;
            tam++;
        }
    }

    // ordena o vetor auxiliar com qsort
    qsort(&ord[0], tam, sizeof(print_t), cmpfunc);

    for (k = 0; k < tam; k++)
        printf("%d,T%d,%d\n", ord[k].key, ord[k].tbl, ord[k].pos);
}