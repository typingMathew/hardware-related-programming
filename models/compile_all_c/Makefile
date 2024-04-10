# advanced Makefile using wildcards to compile all c files
# author typingMathew, inspired by https://opensource.com/article/18/8/what-how-makefile
# Usage:
# make        # compile all c to binary
# make run	  # run all binary
# make clean  # remove all binaries and objects

.PHONY = all run clean

CC = gcc # compiler to use

LINKERFLAG = -lm

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)
RUNS := $(SRCS:%.c=%_go)

all: ${BINS}

%: %.o
	${CC} ${LINKERFLAG} $< -o $@

%.o: %.c
	${CC} -c $<

run:
	@printf 'Executing Binaries \u2620\n'
	@for file in ${BINS}; do \
		./$$file ; \
	done

clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${BINS}