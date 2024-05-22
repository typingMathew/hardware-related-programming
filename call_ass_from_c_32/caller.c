// Inkludieren der C Standard I/O Bibliothek
#include <stdio.h>
// Inkludieren der C Standard Bibliothek
#include<stdlib.h>

// Deklarieren der externen Funktion add_ints, die zwei Integer Zahlen übergeben bekommt und eine zurückliefert. 
extern int add_ints(int, int, int);

// Definieren der Hauptfunktion main,
// diese bekommt eine Integer Zahl (Anzahl an Parametern inklusive dem Programmnamen) und einen Pointer auf ein konstantes Array von Zeichen (Programmname und Parameter) übergeben
// und liefert einen Integerwert zurück.
int main(int argc, char const *argv[]) {
    // Prüfen, ob dem Programm nicht genau vier Parameter (inklusive Programmnamen) übergeben worden
    if (argc != 4) {
        // Ausgabe, wie das Programm zu bedienen ist. Dazu wird der Programmname aus dem Argumenten-Array verwendet.
        printf("Usage: %s <int> <int> <int>\n", argv[0]);
        // Beenden des Programmes mit einem Fehlercode
        exit(EXIT_FAILURE);
    }

    // Umwandeln des ersten Parameters in eine Integer Zahl und speichern dieser in der Variable a
    int a = atoi(argv[1]);
    // Umwandeln des zweiten Parameters in eine Integer Zahl und speichern dieser in der Variable b
    int b = atoi(argv[2]);
    // Umwandeln des dritten Parameters in eine Integer Zahl und speichern dieser in der Variable c
    int c = atoi(argv[3]);

    // Aufrufen der Funktion add_ints mit den Variablen a, b und c und Speichern des Rückgabewertes in der Variable sum
    int sum = add_ints(a, b, c);

    // Ausgabe der Variable a, b, c und sum
    printf("%i + %i + %i = %i\n", a, b, c, sum);
    // Beenden des Programmes mit einem Erfolgscode
    exit(EXIT_SUCCESS);
}
