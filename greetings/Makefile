# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all run_all clean

compiler = gcc
source := $(wildcard *.c)
destination := $(source:%.c=%)
runables := $(destination:%=%_go)
parameter = -Wall
arch = -m64

all: ${destination}

%: %.o
	@echo "Checking.."
	${compiler} $< -o $@

%.o: %.c
	@echo "Creating object.."
	${compiler} ${source} -o ${destination} ${parameter} ${arch}

run: ${runables}

%_go:
	./$* 50 10000 &

clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${destination}