#include "codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define encode 0
#define decode 1

typedef struct threadNode
{
    pthread_t t;
    char buf[512];
    struct threadNode *next;
} node, *pnode;
pnode initNode()
{
    pnode pn = (pnode)malloc(sizeof(node));
    pn->next = NULL;
    return pn;
}
void freeAllNodes(pnode start)
{
    pnode temp;
    while (start != NULL)
    {
        temp = start;
        start = start->next;
        free(temp);
    }
}

int main(int argc, char const *argv[])
{
    int key, whatToDo;
    pnode start = NULL;
    pnode end = start;

    if (argc != 3)
    {
        printf("coder key -e < my_original_file > encripted_file\n");
        return 0;
    }
    key = atoi(argv[1]);
    if (!strcmp(argv[2], "-e"))
    {
        whatToDo = encode;
    }
    else if (!strcmp(argv[2], "-d"))
    {
        whatToDo = decode;
    }
    else
    {
        printf("-e xor -d!\n");
        return 0;
    }
    start = initNode();
    end = start;
    while (scanf("%s", end->buf) != EOF)
    {
        if (whatToDo == encode)
        {
            pthread_create(&end->t, NULL, encrypt, (end->buf, key));
        }
        else if (whatToDo == decode)
        {
            pthread_create(&end->t, NULL, decrypt, (end->buf, key));
        }
        end->next = initNode();
        end = end->next;
    }
    pnode temp;
    while (start!=NULL)
    {
        pthread_join(start->t,NULL);
        printf("%s", start->buf);
        temp = start;
        start = start->next;
        free(temp);
    }
    

    // freeAllNodes(start);
    return 0;
}
