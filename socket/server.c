#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// öffnet einen IPv6 Sockets
int oeffne_socket();
// bindet eine IPv6-Adresse an einen Socket
void binde_socket(int socket_fd);
// aktiviert eine Warteschlange für eingehende Verbindungen
void hoere_auf_socket(int socket_fd);
// behandelt eine Client-Verbindungsanfrage
void behandel_client(int client_fd);

int main(int argc, char const *argv[])
{
    int ret;
    
    // Socket-Datei-Deskriptor
    int socket_fd = oeffne_socket();

    binde_socket(socket_fd);

    hoere_auf_socket(socket_fd);

    // Schleife für die Verarbeitung von Client-Anfragen
    for (;;)
    {
        // Warten auf und akzeptieren einer Client-Anfrage
        ret = accept(socket_fd, NULL, NULL);
        // Fehlerbehandlung
        if (ret < 0)
        {
            perror("accept failed\n");
            return 4;
        }
        // Datei-Deskriptor für die Verbindung zum Client
        int client_fd = ret;

        // Gabelung des Programms, um sowohl Clientanfrage zu bearbeiten,
        // als auch weiterhin auf neue Anfragen reagieren zu können
        ret = fork();
        // Fehlerbehandlung
        if (ret < 0)
        {
            perror("fork failed\n");
            exit(5);
        }
        // Fall für den Vater-Prozess
        else if (ret)
        {
            // Schließen des Client-Sockets, da dieser nichtmehr benötigt wird
            ret = close(client_fd);
            // Fehlerbehandlung
            if (ret < 0)
            {
                perror("close failed\n");
                exit(6);
            }
        }
        // Fall für den Sohn-Prozess
        else
        {
            // Schließen des Socket-FD, da dieser nichtmehr benötigt wird

            ret = close(socket_fd);
            // Fehlerbehandlung
            if (ret < 0)
            {
                perror("close failed\n");
                exit(7);
            }
            
            // Kommunikation mit dem Client
            behandel_client(client_fd);

            // Schließen des Client-Sockets
            close(client_fd);
            // Beenden des Sohn-Prozesses
            return 0;
        }

    }
    
    return 0;
}

int oeffne_socket()
{
    int ret;

    // Kommunikations-Domäne (Protokoll-Familie):
    //      AF_UNIX = Systeminterne Kommunikation
    //      AF_INET6 = Kommunikation über IPv6
    int domain = AF_INET6;
    // Kommunikations-Typ:
    //      SOCK_STREAM = TCP: Verbindungsorientiert, Byte-Stream
    //      SOCK_DGRAM = UDP: Verbindungslos, Datagramme
    int type = SOCK_STREAM;
    // Protokoll: (0 = Standardprotokoll)
    int protocol = 0;
    // Erzeugen eines Sockets
    ret = socket(domain, type, protocol);
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("socket claim failed\n");
        exit(1);
    }

    return ret;
}

void binde_socket(int socket_fd)
{
    int ret;
    // Struktur für die IPv6 Adresse des Servers
    struct sockaddr_in6 addr;
    // Protokollfamilie IPv6
    addr.sin6_family = AF_INET6,
    // Port 12321
    addr.sin6_port = htons(12321),
    // Adresse des Servers
    addr.sin6_addr = in6addr_any;

    // Binden des Sockets an die Adresse
    ret = bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr));
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("bind failed\n");
        exit(2);
    }
}

void hoere_auf_socket(int socket_fd)
{
    int ret;
    // Warteschlange für eingehende Verbindungen
    ret = listen(socket_fd, 5);
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("listen failed\n");
        exit(3);
    }
}

void behandel_client(int client_fd)
{
    // Schleife für die Kommunikation mit dem Client
    for (;;)
    {
        // Pufferspeicher für die Nachricht
        char buffer[1024];

        // Empfangen der Nachricht
        int ret = recv(client_fd, buffer, sizeof(buffer)-1, 0);
        // Fehlerbehandlung
        if (ret < 0)
        {
            perror("receive failed\n");
            exit(8);
        }
        // Fall einer beendeten Verbindung
        else if (ret == 0)
        {
            break;
        }

        // Null-Byte an das Ende der Nachricht setzen
        buffer[ret] = '\0';

        // Ausgabe der empfangenen Nachricht
        printf("Received: %s\n", buffer);

        // Auswahl der Antwort
        if (strcmp(buffer, "Ich will nicht mehr!") == 0)
        {
            strcpy(buffer, "Nein");
        }
        else if (strcmp(buffer, "Doch") == 0)
        {
            strcpy(buffer, "Ohh");
        }

        ret = send(client_fd, buffer, strlen(buffer), 0);
        // Fehlerbehandlung
        if (ret < 0)
        {
            perror("send failed\n");
            exit(9);
        }
    }
}
