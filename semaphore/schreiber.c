#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Hilfsstruktur zum Reservieren
// Dekrementiert die Semaphore
struct sembuf p = { 0, -1, SEM_UNDO};
// Hilfsstruktur zum Freigeben
// Inkrementiert die Semaphore
struct sembuf v = { 0, +1, SEM_UNDO};

// Funktion zum aktiven Warten
void active_wait(size_t delay);

// Erzeugt eine neue Semaphore und initialisiert ihren Wert auf init
int create_new_semaphor(int init);


int main(int argc, char const *argv[])
{
    // Fehlerprüfung
    if (argc != 2)
    {
        printf("usage: %s char_count\n", argv[0]);
        exit(10);
    }
    // Anzahl der Zeichen, die ausgegeben werden sollen
    int char_count = atoi(argv[1]);
    
    // Initialisierung
    // Zufällige Zahlen generieren, indem der Seed auf die aktuelle Zeit gesetzt wird
    srand(time(NULL));
    // Deklaration der Variablen
    // c: Zeichen, das ausgegeben wird
    char c;
    // ret_val: Rückgabewert der Externen-Operationen
    // sem_write: Identifikator der Semaphore zum Schreiben auf Standard-Out
    // sem_block: Identifikator der Semaphore zum Ent-Blockieren des anderen Prozesses
    int ret_val, sem_write, sem_block;
    // Identifikator der Semaphore zum Schreiben auf Standard-Out
    const int sem_write_dad = create_new_semaphor(1);
    // Identifikator der Semaphore zum Schreiben auf Standard-Out
    const int sem_write_son = create_new_semaphor(0);

    // Gabelung des Programms
    int ret = fork();
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("fork failed\n");
        return 1;
    }
    // Fallunterscheidung: das Programm ist Sohn
    else if (ret == 0)
    {
        sem_write = sem_write_son;
        sem_block = sem_write_dad;
        c = 's';
    }
    // Fallunterscheidung: das Programm ist Vater
    else
    {
        sem_write = sem_write_dad;
        sem_block = sem_write_son;
        c = 'V';
    }

    for (int i = 0; i < 256; i++)
    {
        // Warten einer zufälligen Zeit
        int w = rand() % 4000;
        active_wait(w);
        // Versuchen die eigene Semaphore zu bekommen
        // Dazu wird versucht die Operation p (Reservieren, Arg 2) einmal (Arg 3) auszuführen
        ret_val = semop(sem_write, &p, 1);
        // Fehlerbehandlung
        if(ret_val < 0)
        {
            perror("semop p");
            exit(13);
        }

        // Ausgabe der Zeichen
        for (size_t i = 0; i < char_count; i++)
        {
            putchar(c);
        }
        // Leeren des Buffers --> direkte Ausgabe
        fflush(stdout);
        
        // Freigeben der Semaphore für den anderen Prozess
        ret_val = semop(sem_block, &v, 1);
        // Fehlerbehandlung
        if(ret_val < 0)
        {
            perror("semop p");
            exit(13);
        }
        
    }
    // Warten auf den Sohn
    wait(NULL);
    putchar('\n');
    exit(EXIT_SUCCESS);
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

int create_new_semaphor(int init)
{
    int ret_val, sem_id;
    // Erstellen der Semaphore
    // Argument 1 bestimmt den Key (0)
    key_t key = 0;
    // Argument 2 bestimmt die Anzahl an Semaphoren (1)
    int nsems = 1;
    // Argument 3 bestimmt den Modus: 
    //   -  0600 steht für die Berechtigungen (User-Group-All) --> (RW--)
    //   -  Außerdem wird durch IPC_CREAT festgelegt, dass eine neue Semaphore erstellt werden soll, 
    //      falls noch keine mit dem Key existiert
    int flags = 0600 | IPC_CREAT;
    ret_val = semget(key, nsems, flags);
    // Fehlerbehandlung
    if(ret_val < 0)
    {
        perror("semget fehlgeschlagen"); exit(11);
    }
    // Speichern des Identifikators der Semaphore
    sem_id = ret_val;

    // Initialisieren der Semaphore mit dem Wert init
    // dazu wird das Makro SETVAL genutzt
    ret_val = semctl(sem_id, 0, SETVAL, init);
    // Fehlerbehandlung
    if (ret_val < 0)
    {
        perror("semctl"); exit(12);
    }

    return sem_id;
}
