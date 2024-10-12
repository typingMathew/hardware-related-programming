#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Schlüsselwert der Semaphore,
// damit sowohl Vater als auch Kind die gleiche referenzieren
#define SEM_KEY 0x1111

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

// Hilfsstruktur zum Reservieren
// Dekrementiert die Semaphore
struct sembuf p = { 0, -1, SEM_UNDO};
// Hilfsstruktur zum Freigeben
// Inkrementiert die Semaphore
struct sembuf v = { 0, +1, SEM_UNDO};

void active_wait(size_t delay);


int main(int argc, char const *argv[])
{
    // Initialisierung
    srand(time(NULL));
    char c;
    int ret_val;
    // Erstellen der Semaphore
    // Argument 2 bestimmt die Anzahl an Semaphoren (1)
    // Argument 3 bestimmt den Modus: 0666 steht für die Berechtigungen 
    //      (User-Group-All) --> (RW-RW-RW)
    //      Außerdem wird durch IPC_CREAT festgelegt, dass eine neue Semaphore erstellt werden soll, falls noch keine vorhanden ist
    ret_val = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    // Fehlerbehandlung
    if(ret_val < 0)
    {
        perror("semget fehlgeschlagen"); exit(11);
    }
    const int id = ret_val;
    // Initialisieren der Semaphore mit dem Wert 1 (da eine Ressource)
    union semun u;
    u.val = 1;
    // Setzen des Wertes der Semaphore auf den Wert von u.val
    // dazu wird das Makro SETVAL genutzt
    ret_val = semctl(id, 0, SETVAL, u);
    // Fehlerbehandlung
    if (ret_val < 0)
    {
        perror("semctl"); exit(12);
    }

    // Gabelung des Programms
    int ret = fork();
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("fork failed\n");
        return 1;
    }
    // Fallunterscheidung das Programm ist Sohn
    else if (ret == 0)
    {
        c = 's';
    }
    // Fallunterscheidung das Programm ist Vater
    else
    {
        c = 'V';
    }

    int count = 0;
    for (size_t i = 0; i < 256; i++)
    {
        int w = rand() % 1000;
        active_wait(w);
        // Versuchen die Semaphore zu bekommen
        // Dazu wird versucht die Operation p (Reservieren, Arg 2) einmal (Arg 3) auszuführen
        ret_val = semop(id, &p, 1);
        // Fehlerbehandlung
        if(ret_val < 0)
        {
            perror("semop p"); exit(13);
        }

        putchar(c);
        putchar(c);
        fflush(stdout);
        
        // Freigeben der Semaphore
        ret_val = semop(id, &v, 1);
        // Fehlerbehandlung
        if(ret_val < 0)
        {
            perror("semop p"); exit(13);
        }
        

        count++;
    }
    wait(NULL);
    putchar('\n');
    return 0;
}

void active_wait(size_t delay)
{
    for (size_t i = 0; i < delay; i++)
    {
        for (size_t j = 0; j < delay; j++)
        {
            j++;
            j--;
        }
    }
}
