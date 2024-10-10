# Usage:
# make [compile] 				# compile anton.c to binary if not up-to-date
# make run ARGS="arg1 arg2"		# eventually compile and surely execute
# make clean  					# remove anton binary

.PHONY = compile run clean # diese sind keine Datei

compiler = gcc
source = anton.c
destination = anton
parameter = -Wall
arch = -m64
# Standardargumente für das Programm
ARGS = 50 10000

# Befehlsstruktur von Makefile:
# Ziel: Vorbedingung
# 	 Anweisung
#	 Anweisung

compile: ${destination}

${destination}: ${source} # dabei wird implizit geprüft, ob source neuer als dest ist!
	${compiler} ${source} -o ${destination} ${parameter} ${arch}

run: compile # eine binary ist die Vorbedingung von einer Ausführung
	./${destination} $(ARGS)

clean:
	@echo "Cleaning up..."
	rm -vf ${destination}