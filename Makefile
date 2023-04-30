.PHONY: all setLib
all: setLib task stdinExample main

task:	codec.h basic_main.c
	gcc basic_main.c -L. -l Codec -o encoder

stdinExample:	stdin_main.c
		gcc stdin_main.c ./libCodec.so -L. -l Codec -o tester
main:	main.c
	gcc main.c -L. -l Codec -o main -lpthread

.PHONY: clean 
setLib:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:
clean:
	-rm encoder tester main 2>/dev/null

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/
# ./main 12 -e <input.txt >output.txt
# ./main 12 -d < output.txt >input.txt 
