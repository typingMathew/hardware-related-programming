# Usage:
# make [compile] 	# compile anton.c to binary if not up-to-date
# make run	  		# eventually compile and surely execute
# make clean  		# remove anton binary

.PHONY = all clean # diese sind keine Datei

compiler = gcc
source = anton.c
destination = anton
parameter = -Wall
arch = -m64

# Befehlsstruktur von Makefile:
# Ziel: Vorbedingung
# 	 Anweisung
#	 Anweisung

compile: ${destination}

${destination}: ${source} # dabei wird implizit geprüft, ob source neuer als dest ist!
	${compiler} ${source} -o ${destination} ${parameter} ${arch}

run: compile # eine binary ist die Vorbedingung von einer Ausführung
	./${destination} 50 10000

clean:
	@echo "Cleaning up..."
	rm -vf ${destination}