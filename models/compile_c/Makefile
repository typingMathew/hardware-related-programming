# basic Makefile to compile one c file
# author typingMathew, inspired by https://opensource.com/article/18/8/what-how-makefile
CC = gcc

compile: hello.c
	@echo "Compiling hello.c ..."
	${CC} hello.c -o hello

run:
	./hello

clean:
	@echo "Cleaning up..."
	rm -rvf *.o hello