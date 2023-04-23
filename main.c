#include "codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define encode 0
#define decode 1
int main(int argc, char const *argv[])
{
    int key, whatToDo;
    FILE *inputFile;
    FILE *outputFile;
    if (argc != 5)
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
    if((inputFile = fopen(argv[3], "r+"))==NULL)
    {
        printf("cant open %s\n", argv[3]);
	    return 0;
    }
    if((outputFile = fopen(argv[4], "w+")) == NULL)
    {
        printf("cant open %s\n", argv[4]);
	    return 0;
    }

    char buf[1024];
    fread(buf, sizeof(char), 1024, inputFile);
    printf("input: %s\n", buf);
    encrypt(buf, key);
    printf("output: %s\n", buf);
    fwrite(buf,sizeof(char), strlen(buf), outputFile);
    
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
