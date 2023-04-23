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
int key, whatToDo;
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

void *runThread(char *buf)
{
    if (whatToDo == encode)
    {
        encrypt(buf, key);
    }
    else if(whatToDo == decode)
    {
        decrypt(buf,key);
    }
    else
    {
        printf("erro\n");
        exit(0);
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
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
    while (fgets(end->buf, 512, stdin) != NULL)
    {
        pthread_create(&end->t, NULL, (void *)runThread, end->buf);
        end->next = initNode();
        end = end->next;
    }
    pnode temp;
    while (start != NULL)
    {
        pthread_join(start->t, NULL);
        printf("%s", start->buf);
        temp = start;
        start = start->next;
        free(temp);
    }

    // freeAllNodes(start);
    return 0;
}
