#ifndef HASH_H_
#define HASH_H_

typedef struct hash
{
    int *keys;
    int tam;
} hash_t;

hash_t *create_hash_table();

hash_t *exclude_hash_table(hash_t *t);

int h1(int k, int m);

int h2(int k, int m);

int include_key(hash_t *t1, hash_t *t2, int k);

int search_key(hash_t *t1, hash_t *t2);

int print_table(hash_t *t);

#endif