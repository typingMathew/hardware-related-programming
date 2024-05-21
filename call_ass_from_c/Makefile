# Usage:
# make [compile]	# compile both assembler and c file to objects and link them
# make run			# eventually compile and surely execute
# make clean  		# remove binary and object files

.PHONY = compile compile_c compile_asm link run clean

# Deklarationen
c_compiler = gcc
c_source = caller.c
c_destination = caller.o
c_parameter = -c -Wall -g
c_arch = -m64

asm_compiler = nasm
asm_source = callee.asm
asm_destination = callee.o
asm_parameter = ""
asm_arch = -f elf64

final_destination = add
linker = gcc


compile: compile_asm compile_c link

compile_c: ${c_destination}

compile_asm: ${asm_destination}

${c_destination}: ${c_source} # dabei wird implizit geprüft, ob source neuer als dest ist!
	${c_compiler} ${c_source} -o ${c_destination} ${c_parameter} ${c_arch}

${asm_destination}: ${source} # dabei wird implizit geprüft, ob source neuer als dest ist!
	${asm_compiler} ${asm_arch} ${asm_source} -o ${asm_destination} ${asm_parameter}
	
link: ${final_destination}

${final_destination}: ${asm_destination} ${c_destination}
	${linker} ${c_destination} ${asm_destination} -o ${final_destination}


run: compile
	@echo "Running..."
	./${final_destination} 2 3


clean:
	@echo "Cleaning up..."
	rm -vf ${asm_destination}
	rm -vf ${c_destination}
	rm -vf ${final_destination}