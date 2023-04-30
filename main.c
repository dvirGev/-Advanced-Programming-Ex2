#include "codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define encode 0
#define decode 1

typedef struct threadNode
{
    char buf[512];
    struct threadNode *next;
} node, *pnode;

int key, whatToDo;
pthread_mutex_t lock;
pnode start = NULL;
pnode end = NULL;
pnode initNode()
{
    pnode pn = (pnode)malloc(sizeof(node));
    pn->next = NULL;
    return pn;
}
char *readFromStin()
{
    
    pthread_mutex_lock(&lock);
    char *res = fgets(end->buf, 512, stdin);
    end->next = initNode();
    end = end->next;
    pthread_mutex_unlock(&lock);
    return res;
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

void *runThread()
{
    if (whatToDo == encode)
    {
        char *buf;
        while ((buf = readFromStin()) != NULL)
        {
            encrypt(buf, key);
        }
    }
    else if(whatToDo == decode)
    {
        char *buf;
        while ((buf = readFromStin()) != NULL)
        {
            decrypt(buf, key);
        }
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

    pthread_t threads[5];
    for (size_t i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, (void *)runThread, NULL);
    }
    for (size_t i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pnode temp;
    while (start != NULL)
    {
        printf("%s", start->buf);
        temp = start;
        start = start->next;
        free(temp);
    }

    return 0;
}
