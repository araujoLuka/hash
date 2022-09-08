#ifndef HASH_H_
#define HASH_H_
#define H_TAM 11

typedef struct key
{
    int value;
    int isValid;
} key_t;

typedef struct hash
{
    key_t keys[H_TAM];
    int tam;
} hash_t;

hash_t *create_hash_table();

hash_t *exclude_hash_table(hash_t *t);

int h1(int k, int m);

int h2(int k, int m);

int include_key(hash_t *t1, hash_t *t2, int k);

int search_key(hash_t *t1, hash_t *t2, int k);

int remove_key(hash_t *t1, hash_t *t2, int k);

void print_table(hash_t *t);

#endif