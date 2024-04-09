# Usage:
# make [compile] 	# compile adding.c to binary if not up-to-date
# make run	  		# eventually compile and surely execute
# make clean  		# remove anton binary

.PHONY = compile run clean # diese sind keine Datei

compiler = gcc
source = adding.c
destination = adding
parameter = -Wall
arch = -m64

compile: ${destination}

${destination}: ${source} # dabei wird implizit geprüft, ob source neuer als dest ist!
	${compiler} ${source} -o ${destination} ${parameter} ${arch}

run: compile # eine binary ist die Vorbedingung von einer Ausführung
	./${destination}

clean:
	@echo "Cleaning up..."
	rm -vf ${destination}