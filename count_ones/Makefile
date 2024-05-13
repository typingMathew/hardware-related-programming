# Usage:
# make [compile] 	# compile count_ones.c to binary if not up-to-date
# make run	  		# eventually compile and surely execute
# make clean  		# remove count_ones binaries

.PHONY = compile run clean # diese sind keine Datei

compiler = gcc
source = count_ones.c
destination = count_ones_c.o
parameter = -Wall
arch = -m64


compile: ${destination}

${destination}: ${source} # dabei wird implizit geprüft, ob source neuer als dest ist!
	${compiler} ${source} -o ${destination} ${parameter} ${arch}

run: compile # eine binary ist die Vorbedingung von einer Ausführung
	./${destination} 2000

clean:
	@echo "Cleaning up..."
	rm -vf ${destination}
	rm -vf ${object}