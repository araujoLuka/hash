#include "libhash.h"
#include <stdlib.h>
#include <stdio.h>

hash_t *create_hash_table()
{
    hash_t *t;

    if (!(t = malloc(sizeof(hash_t))))
    {
        fprintf(stderr, "Error on hash tabble alocation\n");
        return NULL;
    }

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
    return m * (int)(k * 0.9f - (k * 0.9f));
}

int include_key(hash_t *t1, hash_t *t2, int k)
{
    int i;
    node_h k_temp;

    i = h1(k, t1->tam);
    if (t1->keys[i].isValid == 0)
    {
        t1->keys[i].value = k;
        t1->keys[i].isValid = 1; 
        return 1;
    }
    
    if (t1->keys[i].value != k)
    {
        k_temp = t1->keys[i];

        t1->keys[i].value = k;
        t1->keys[i].isValid = 1;

        t2->keys[h2(k_temp.value, t2->tam)] = k_temp;
        
        return 2;
    }

    return 0;
}

int search_key(hash_t *t1, hash_t *t2, int k)
{
    int index = h1(k, t1->tam);
    if(!t1->keys[index].isValid || t1->keys[index].value != k)
    {
        index = h2(k, t2->tam);
        if(!t2->keys[index].isValid || t2->keys[index].value != k)
            return -1;
        return index;
    }
    return index;
}

void print_table(hash_t *t) 
{
    int i;
    for (i = 0; i < t->tam; i++) 
    {
        if(t->keys[i].isValid)
            printf("Key %2d || Value: %2d\n", i, t->keys[i].value);
    }
}