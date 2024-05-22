// Inkludieren der C Standard I/O Bibliothek
#include<stdio.h>
// Inkludieren der C Standard Bibliothek
#include<stdlib.h>

// Deklarieren der externen Funktion add_ints, die zwei Integer Zahlen übergeben bekommt und eine zurückliefert. 
extern int add_ints(int, int);

// Definieren der Hauptfunktion main,
// diese bekommt eine Integer Zahl (Anzahl an Parametern inklusive dem Programmnamen) und einen Pointer auf ein konstantes Array von Zeichen (Programmname und Parameter) übergeben
// und liefert einen Integerwert zurück.
int main(int argc, char const *argv[]) {
    // Prüfen, ob dem Programm nicht genau drei Parameter (inklusive Programmnamen) übergeben worden
    if (argc != 3) {
        // Ausgabe, wie das Programm zu bedienen ist. Dazu wird der Programmname aus dem Argumenten-Array verwendet.
        printf("Usage: %s <int> <int>", argv[0]);
        // Beenden des Programmes mit einem Fehlercode
        exit(EXIT_FAILURE);
    }

    // Umwandeln des ersten Parameters in eine Integer Zahl und speichern dieser in der Variable a
    int a = atoi(argv[1]);
    // Umwandeln des zweiten Parameters in eine Integer Zahl und speichern dieser in der Variable b
    int b = atoi(argv[2]);

    // Aufrufen der Funktion add_ints mit den Variablen a und b und Speichern des Rückgabewertes in der Variable sum
    int sum = add_ints(a, b);

    // Ausgabe der Variable a, b und sum
    printf("%i + %i = %i\n", a, b, sum);
    // Beenden des Programmes mit einem Erfolgcode
    exit(EXIT_SUCCESS);
}
