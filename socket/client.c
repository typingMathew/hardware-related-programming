#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int send_and_receive(int socket_fd);

int main(int argc, char const *argv[])
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
        return 1;
    }
    // Socket-Deskriptor
    int socket_fd = ret;

    // Struktur für die IPv6 Adresse des Clients
    struct sockaddr_in6 addr;
    // Protokollfamilie IPv6
    addr.sin6_family = AF_INET6,
    // Port 12321
    addr.sin6_port = htons(12321),
    // Adresse des Clients
    inet_pton(AF_INET6, "::1", &addr.sin6_addr);

    connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr));

    ret = send_and_receive(socket_fd);
    // Fehlerbehandlung
    if (ret != 0)
    {
        perror("send_and_receive failed\n");
        return 2;
    }

    ret = close(socket_fd);
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("close failed\n");
        return 3;
    }

    return 0;
}

int send_and_receive(int socket_fd){
    // Puffer für die Nachricht
    char buffer[1024];

    int ret;

    // Schleife für unbegrenzte Nutzereingaben
    for (
        // Lesen der Nutzereingabe
        ret = read(STDIN_FILENO, buffer, sizeof(buffer)-1);
        // Schleifenabbruch, wenn
        //      - Nutzereingabe leer ist (Ctrl+D oder Leerzeile)
        //      - Fehler beim Lesen aufgetreten ist
        ret > 1;
        // Lesen der Nutzereingabe
        ret = read(STDIN_FILENO, buffer, sizeof(buffer)-1))
    {
        // Länge der eingelesenen Nachricht
        int len = ret;
        // Setzen des Null-Bytes (anstatt des Zeilenumbruchs)
        buffer[len-1] = '\0';
        // Senden der Nachricht
        ret = send(socket_fd, buffer, len, 0);
        // Fehlerbehandlung
        if (ret < 0)
        {
            perror("send failed\n");
            return 2;
        }

        // Empfangen der Nachricht
        ret = recv(socket_fd, buffer, sizeof(buffer)-1, 0);
        // Fehlerbehandlung
        if (ret < 0)
        {
            perror("receive failed\n");
            return 3;
        }
        // Setzen des Null-Bytes
        buffer[ret] = '\0';
        // Ausgabe der Nachricht
        printf("Received: %s\n", buffer);
    }
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("read failed\n");
        return 1;
    }
    

    printf("Abbausequenz eingeleitet\n");
    // Senden der vorletzten Nachricht
    ret = send(socket_fd, "Ich will nicht mehr!", 20, 0);
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("send failed\n");
        return 4;
    }
    printf("Send: Ich will nicht mehr!\n");
    // Empfangen der Nachricht
    ret = recv(socket_fd, buffer, sizeof(buffer)-1, 0);
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("receive failed\n");
        return 5;
    }
    // Setzen des Null-Bytes
    buffer[ret] = '\0';
    // Ausgabe der Nachricht
    printf("Received: %s\n", buffer);

    // Senden der letzten Nachricht
    ret = send(socket_fd, "Doch", 4, 0);
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("send failed\n");
        return 6;
    }
    printf("Send: Doch\n");
    // Empfangen der Nachricht
    ret = recv(socket_fd, buffer, sizeof(buffer)-1, 0);
    // Fehlerbehandlung
    if (ret < 0)
    {
        perror("receive failed\n");
        return 7;
    }
    // Setzen des Null-Bytes
    buffer[ret] = '\0';
    // Ausgabe der Nachricht
    printf("Received: %s\n", buffer);

    return 0;
}