#include "libhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFSIZE 10
#define DEBUG 0 // set to print functions logs

int main()
{
    int key, i, n, ret;
    char cmd[BUFFSIZE+1], op;
    hash_t *t1, *t2;

    // hash elements counter
    n = 0;

    // return definer
    ret = 0;
    
    t1 = create_hash_table();
    t2 = create_hash_table();

    if (!t1 || !t2)
    {
        fprintf(stderr, "-> Error on hash tabble alocation\n");
        ret = -1;
    }

    while(ret == 0){
        if (!fgets(cmd, BUFFSIZE, stdin))
            break;
        
        if (!strstr(cmd, " "))
        {
            op = (char)*strtok(cmd, "\0");
            if (op == '0')
            {
                printf("-> Execution stopped manually\n");
                break;
            }
            else
                op = 'x';
        }
        else
        {
            op = (char)*strtok(cmd, " ");
            key = atoi(strtok(NULL, "\0"));
        }

        switch ((int)op)
        {
        case 'i':
            i = include_key(t1, t2, key);
            if (i == -1)
            {
                fprintf(stderr, "-> Hash overflow\n");
                ret = 1;
            }
            else if (i > 0)
                n++;

            if (DEBUG)
            {
                if (i == 0)
                    printf("Key: %2d -> Duplicated insert\n", key);
                else if (i == 1)
                    printf("Key: %2d -> Key included without colision\n", key);
                else
                    printf("Key: %2d -> Key included with colision\n", key);
            }
            break;

        case 'b':
            i = search_key(t1, t2, key);

            if (DEBUG)
            {
                if (i == -1)
                    printf("Key: %2d -> Key isn't here\n", key);
                else if (i < H_TAM)
                    printf("Key: %2d -> Hash: %d - p: %d\n", key, 1, i);
                else
                    printf("Key: %2d -> Hash: %d - p: %d\n", key, 2, i);
            }
            break;

        case 'r':
            i = remove_key(t1, t2, key);
            if (i > 0)
                n--;

            if (DEBUG)
            {
                if (i == 0)
                    printf("Key: %2d -> Key isn't here\n", key);
                else if (i == 1)
                    printf("Key: %2d -> Key removed from T1\n", key);
                else if (i == 2)
                    printf("Key: %2d -> Key removed from T2\n", key);
            }
            break;
        
        default:
            fprintf(stderr, "-> Invalid command\n");
            ret = 2;
            break;
        }
    }
    if (DEBUG)
        printf("\n");

    if (ret != -1)
        print_table(t1, t2);
        
    t1 = exclude_hash_table(t1);
    t2 = exclude_hash_table(t2);

    return ret;
}