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