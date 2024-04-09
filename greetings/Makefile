# Usage:
# make [compile]  # compile all c to binary
# make run	      # run all binary
# make clean      # remove ALL binaries

.PHONY = all run clean

compiler = gcc
source := $(wildcard *.c)
destination := $(source:%.c=%)
runables := $(destination:%=%_go)
parameter = -Wall
arch = -m64

compile: ${destination}

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