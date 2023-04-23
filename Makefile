.PHONY: all
all: task stdinExample main

task:	codec.h basic_main.c
	gcc basic_main.c -L. -l Codec -o encoder

stdinExample:	stdin_main.c
		gcc stdin_main.c -L. -l Codec -o tester
main:	main.c
	gcc main.c -L. -l Codec -o main

.PHONY: clean
clean:
	-rm encoder tester main 2>/dev/null

//export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/
