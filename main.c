#include "libhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFSIZE 10

int main()
{
    int key, i;
    char cmd[BUFFSIZE+1], op;
    hash_t *t1, *t2;

    t1 = create_hash_table();
    t2 = create_hash_table();

    while(1){
        if (!fgets(cmd, BUFFSIZE, stdin))
            break;
        
        op = (char)*strtok(cmd, " ");
        if (op == '0')
            break;

        key = atoi(strtok(NULL, "\0"));

        switch ((int)op)
        {
        case 'i':
            i = include_key(t1, t2, key);

            if (i == 0)
                printf("Key: %2d -> Duplicated insert\n", key);
            else if (i == 1)
                printf("Key: %2d -> Key included withou colision\n", key);
            else
                printf("Key: %2d -> Key included with colision\n", key);

            break;
        case 'b':
            i = search_key(t1, t2, key);

            if (i == -1)
                printf("Key: %2d -> Key isn't here\n", key);
            else
            {
                if (i < H_TAM)
                    printf("Key: %2d -> Hash: %d - p: %d\n", key, 1, i);
                else
                    printf("Key: %2d -> Hash: %d - p: %d\n", key, 2, i);
            }
            
            break;
        case 'r':
            break;
        }
    }
    printf("* HASH 1 *\n");
    print_table(t1);

    printf("\n* HASH 2 *\n");
    print_table(t2);
    
    t1 = exclude_hash_table(t1);
    t2 = exclude_hash_table(t2);

    return 0;
}