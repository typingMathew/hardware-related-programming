# Usage:
# make [compile] 	# compile hello.asm to binary and link if not up-to-date
# make run	  		# eventually compile and surely execute
# make clean  		# remove hello binary + object

.PHONY = compile run clean # diese sind keine Datei

compiler = nasm
linker = ld
source = hello.asm
object = hello.o
destination = hello
parameter = ""
arch = -f elf64

# Befehlsstruktur von Makefile:
# Ziel: Vorbedingung
# 	 Anweisung
#	 Anweisung

compile: ${destination}

${destination}: ${source} # dabei wird implizit geprüft, ob source neuer als dest ist!
	${compiler} ${arch} ${source} -o ${object} ${parameter}
	${linker} -o ${destination} ${object}

run: compile # eine binary ist die Vorbedingung von einer Ausführung
	./${destination}

clean:
	@echo "Cleaning up..."
	rm -vf ${object}
	rm -vf ${destination}


