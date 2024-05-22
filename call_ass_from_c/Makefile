# Usage:
# make [link]		# compile c and assemble assembly to objects and link them to a executable
# make run			# eventually do the link above and surely execute
# make clean  		# remove binary files

# Die hier deklarierten Bezeichner sollen vom Make nicht als Dateinamen interpretiert werden
.PHONY = link run clean

# Deklarationen
# Ich benutze den Gnu C Compiler als Compiler für die C Dateien 
compiler = gcc
# Meine C-Source Datei hat den Namen caller.c 
c_source = caller.c
# Mein Zieldateiname für den Compilierten C Code heißt caller.o 
c_object = caller.o
# Folgende Parameter sollen dem GCC übergeben werden:
# -c deaktiviert den Linkingprozess des GCC
# -Wall aktiviert alle Fehler- und Warnungsmeldungen
# -g aktivert die Debugmöglichkeit für den Objektcode (bspw. mit dem DDD)
c_parameter = -c -Wall -g
# Die Zielarchitektur für den compilierten Code ist x86 64 Bit
c_arch = -m64

# Als Assemblierer verwende ich den Netwide Assembler
assembler = nasm
# Meine Assembler-Source Datei hat den Namen callee.asm
asm_source = callee.asm
# Mein Zieldateiname für den Assembler Code heißt callee.o
asm_object = callee.o
# Folgende Parameter sollen dem NASM übergeben werden:
asm_parameter = ""
# -f gibt das Format der Ausgabedatei an (hier 64 Bit ELF)
asm_arch = -f elf64

# Als Linker verwende ich den implizit durch den GCC aufgerufenen LD
linker = gcc
# Mein Zieldateiname für das fertige Programm heißt add.out
final_destination = add.out

# Dies ist der erste Befehl, der ausgeführt wird, wenn make ohne Parameter aufgerufen wird
# link hat als Ziel das fertige Programm
link: ${final_destination}

# Um das fertige Programm zu erstellen, müssen die Assembly- und C- Objektdateien vorhanden sein
# dabei wird implizit geprüft, ob die Objektdateien neuer als ein eventuell vorhandene ausführbare Datei ist und nur dann wird das Linken ausgeführt
${final_destination}: ${asm_object} ${c_object}
#	Es wird ausgegeben, dass das Linken beginnt
	@echo "Linking..."
# 	Der Linker wird mit den beiden Objektdateien aufgerufen, wodurch daraus und aus den im C Quelltext eingebundenen Bibliotheken ein ausführbares Programm entsteht
#	über -o wird dabei der Name der Ausgabedatei festgelegt 
	${linker} ${c_object} ${asm_object} -o ${final_destination}

# Um die C Objektdatei zu erstellen, muss der C Quelltext vorhanden sein
# dabei wird implizit geprüft, ob der Quelltext neuer als eine eventuell vorhandene Objektdatei ist und nur dann wird das Compilieren ausgeführt
${c_object}: ${c_source}
#	Es wird ausgegeben, dass das Compilieren beginnt
	@echo "Compiling..."
#	Der Compiler wird mit dem C Quelltext aufgerufen, wodurch daraus eine Objektdatei entsteht
	${compiler} ${c_source} -o ${c_object} ${c_parameter} ${c_arch}

# Um die Assembly Objektdatei zu erstellen, muss der Assembly Quelltext vorhanden sein
# dabei wird implizit geprüft, ob der Quelltext neuer als eine eventuell vorhandene Objektdatei ist und nur dann wird das Assemblieren ausgeführt
${asm_object}: ${source}
#	Es wird ausgegeben, dass das Assemblieren beginnt
	@echo "Assembling..."
#	Der Assemblierer wird mit dem Assembly Quelltext aufgerufen, wodurch daraus eine Objektdatei entsteht
	${assembler} ${asm_arch} ${asm_source} -o ${asm_object} ${asm_parameter}
	

# Ein Befehl zum Ausführen des Programms. Dafür muss der Linkvorgang abgeschlossen sein
# Durch die implizite Prüfung dabei, wird dies nur ausgeführt, wenn es tatsächlich erforderlich ist
run: link
#	Es wird ausgegeben, dass das Programm gestartet wird
	@echo "Running..."
#	Das fertige Programm wird gestartet, ihm werden die zwei Zahlen 2 und 3 als Argumente übergeben
	./${final_destination} 2 3


# Ein Befehl zum Aufräumen. Dabei werden alle erzeugten Dateien gelöscht
clean:
#	Es wird ausgegeben, dass aufgeräumt wird
	@echo "Cleaning up..."
# 	Die Assembly Objektdatei wird gelöscht
	rm -vf ${asm_object}
#	Die C Objektdatei wird gelöscht
	rm -vf ${c_object}
#	Das fertige Programm wird gelöscht
	rm -vf ${final_destination}