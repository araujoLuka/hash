#ifndef HASH_H_
#define HASH_H_

#define H_TAM 11

typedef struct print_struct
{
    int key;
    int tbl;
    int pos;
} print_t;

typedef struct key_struct
{
    int value;
    int isValid;
} node_h;

typedef struct hash
{
    node_h keys[H_TAM];
    int tam;
} hash_t;

hash_t *create_hash_table();

hash_t *exclude_hash_table(hash_t *t);

int h1(int k, int m);

int h2(int k, int m);

int include_key(hash_t *t1, hash_t *t2, int k);

int search_key(hash_t *t1, hash_t *t2, int k);

int remove_key(hash_t *t1, hash_t *t2, int k);

void print_table(hash_t *t1, hash_t *t2);

#endif