#include "libhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
    return floor(m * (k * 0.9 - floor(k * 0.9)));
}

int include_key(hash_t *t1, hash_t *t2, int k)
{
    int i;
    key_t k_temp;

    i = h1(k, t1->tam);
    if (t1->keys[i].isValid == 0)
    {
        t1->keys[i].value = k;
        t1->keys[i].isValid = 1; 
        return 1 * 100 + i;
    }
    else
    {
        k_temp = t1->keys[i];
        t2->keys[h2(k_temp.value, t2->tam)] = k_temp;
    }
}

int search_key(hash_t *t1, hash_t *t2, int k)
{
    int index = h1(k, t1->tam);
    if(!t1->keys[index].isValid || t1->keys[index].value != k)
    {
        index = h2(k, t2->tam);
        if(!t2->keys[index].isValid || !t2->keys[index].value != k)
            return -1;
        return index + t1->tam;
    }    
    return index;
}

int remove_key(hash_t *t1, hash_t *t2, int k)
{
    int index = search_key(t1, t2, k);

    if(index == -1)
        return 0;

    if (index < t1->tam) 
    {
        t1->keys[index].isValid = 0;
        t1->keys[index].value = 0;
        return 1;
    }
    index -= t1->tam;
    t2->keys[index].isValid = 0;
    t2->keys[index].value = 0;
    return 2;
}

void print_table(hash_t *t) 
{
    int i;
    for (i = 0; i < t->tam; i++) 
    {
        if(t->keys[i].isValid)
            print_table("Key %2d || Value: %2d\n", t, t->keys[i].value);
    }
}