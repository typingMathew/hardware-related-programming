// Inkludieren der C Standard I/O Bibliothek, um die Funktion printf() zur Ausgabe nutzen zu können.
#include<stdio.h>
// Inkludieren der C Standard Bibliothek, um bspw. die Funktionen exit() und atoi() sowie die Konstanten EXIT_FAILURE und EXIT_SUCCESS nutzen zu können.
#include<stdlib.h>

// Deklarieren der externen Funktion add_ints, die zwei Integer Zahlen übergeben bekommt und eine zurückliefert.
// Dies ermöglicht die Funktion, welche später über das ABI eingebunden wird im nachfolgenden Code benutzen zu können.
extern int add_ints(int, int);

// Definieren der Hauptfunktion main,
// diese bekommt eine Integer Zahl (Anzahl an Parametern inklusive dem Programmnamen) und einen Pointer auf ein konstantes Array von Zeichen (Programmname und Parameter) übergeben
// und liefert einen Integerwert zurück.
// Dies ist erforderlich, damit der Compiler ein Binärprogramm erstellen kann.
int main(int argc, char const *argv[]) {
    // Prüfen, ob dem Programm nicht genau drei Parameter (inklusive Programmnamen) übergeben worden.
    // Diese Fehlerprüfung soll eine falsche Benutzung des Programmes verhindern.
    if (argc != 3) {
        // Ausgabe, wie das Programm zu bedienen ist. Dazu wird der Programmname aus dem Argumenten-Array verwendet.
        // Damit wird der Benutzer darauf hingewiesen, wie das Programm korrekt zu bedienen ist.
        printf("Usage: %s <int> <int>\n", argv[0]);
        // Beenden des Programmes mit einem Fehlercode, da es nicht korrekt benutzt wurde.
        exit(EXIT_FAILURE);
    }

    // Umwandeln des ersten Parameters in eine Integer Zahl und speichern dieser in der Variable a, um den Wert später zur Berechnung nutzen zu können.
    int a = atoi(argv[1]);
    // Umwandeln des zweiten Parameters in eine Integer Zahl und speichern dieser in der Variable b, um den Wert später zur Berechnung nutzen zu können.
    int b = atoi(argv[2]);

    // Aufrufen der externen Funktion add_ints mit den Variablen a und b und Speichern des Rückgabewertes in der Variable sum.
    // Dies demonstriert, wie eine Funktion aus einer anderen Datei aufgerufen werden kann.
    int sum = add_ints(a, b);

    // Ausgabe der Variable a, b und sum. Damit wird der Erfolg des Programmes demonstriert.
    printf("%i + %i = %i\n", a, b, sum);
    // Beenden des Programmes mit einem Erfolgcode, da das Programm korrekt und vollständig ausgeführt wurde.
    exit(EXIT_SUCCESS);
}
