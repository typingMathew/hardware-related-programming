# Aufrufkonventionen für x86 ABI Schnittstellen

## 32 Bit Architektur

Vgl. [aaronbloomfield.github.io](https://aaronbloomfield.github.io/pdr/book/x86-32bit-ccc-chapter.pdf)

### Regeln des Aufrufers

1. Bevor eine Subroutine aufgerufen wird, sollten bestimmte Register gespeichert werden, wenn deren Inhalt erhalten werden soll. Diese sind: EAX, ECX und EDX. Zum Speichern dieser während des Subroutinenaufrufs müssen sie auf den Stack gepusht werden.
2. Um Parameter an das aufzurufende Programm zu übergeben, müssen diese in invertierter Reihenfolge (letzter Parameter zuerst) auf den Stack geschrieben werden.
3. Um eine Subroutine aufzurufen wird der CALL Befehl verwendet. Dieser legt die Rückkehraddresse auf den Stack und branched zum Subroutinencode
4. Nach dem die Subroutine zurückgekehrt ist, müssen die Parameter aus 2. aus dem Stack entfernt werden.
5. Der Rückkehrwert der Subroutine ist in dem Register EAX vorzufinden.
6. Um den voherigen Zustand wiederherzustellen, werden die in 1. gespeicherten Registerwerte vom Stack gepoppt und zurückgeschrieben.

### Regeln des Aufgerufenen

1. Zu Beginn der Subroutine sollte der Wert des Registers EBP (Basispointer) auf den Stack gepusht werden und anschließend sollte der Wert des Registers ESP in das Register EBP geschrieben werden. Dies geschieht mit folgenden Anweisungen: > push ebp > mov epb, esp  
Damit setzt die Subroutine den aktuellen Stackpointer als Basispointer, was für den Zugriff auf Parameter und lokale Variablen benötigt wird.
2. Als Nächstes wird Speicher für lokale Variablen reserviert, indem der Stackpointer um den entsprechend benötigten Speicherplatz dekrementiert wird.
3. Darauf müssen die Register, welche von der Funktion genutzt werden und in die Zuständigkeit des Aufrufers fallen auf den Stack gesichert werden. Diese können sein: EBX, EDI und ESI. Nun kann mit der Subroutine begonnen werden.
4. Der Rückgabewert der Subroutine muss in das Register EAX geschrieben werden.
5. Eventuell veränderte Register müssen mit den Sicherungen aus 3. Wiederhergestellt werden.
6. Lokale Variablen müssen deallokiert werden, in dem der Stackpointer wieder auf den Basispointer gesetzt wird > mov esp, ebp
7. Direkt vor dem zurückkehren muss der im Stack gespeicherte (1.) ursprüngliche Basispointer zurück in dessen Register geschrieben werden.
8. Zurückkehren zum Aufrufer durch eine ret Anweisung. Diese poppt die Rückkehraddresse vom Stack.

## 64 Bit Architektur

Vgl. [aaronbloomfield.github.io](https://aaronbloomfield.github.io/pdr/book/x86-64bit-ccc-chapter.pdf)

### Regeln des  Aufrufers

1. Bevor eine Subroutine aufgerufen wird, sollten bestimmte Register gespeichert werden, wenn deren Inhalt erhalten werden soll. Diese sind: R10, R11 und weiter alle Register in die Parameter eingefügt werden. Zum Speichern dieser während des Subroutinenaufrufs müssen sie auf den Stack gepusht werden.
2. Um Parameter an das aufzurufende Programm zu übergeben, müssen diese, einzeln und in Reihenfolge, in die Register: RDI, RSI, RDX, RCX, R8 bzw. R9 geschrieben werden. Falls es mehr als sechs Parameter gibt, werden die restlichen in invertierter Reihenfolge auf den Stack geschrieben.
3. Um eine Subroutine aufzurufen wird der CALL Befehl verwendet. Dieser legt die Rückkehraddresse auf den Stack und branched zum Subroutinencode
4. Nach dem die Subroutine zurückgekehrt ist, müssen eventuelle Zusatzparameter aus 2. vom Stack entfernt werden.
5. Der Rückkehrwert der Subroutine ist in dem Register RAX vorzufinden.
6. Um den voherigen Zustand wiederherzustellen, werden die in 1. gespeicherten Registerwerte vom Stack gepoppt und zurückgeschrieben.

### Regeln des  Aufgerufenen

1. Zur Nutzung von lokalen Variablen werden Register oder Platz auf dem Stack allokiert. Für letzteres wird der Stackpointer um die entsprechend benötigte Platzanzahl dekrementiert.
2. Darauf müssen die Register, welche von der Funktion genutzt werden und in die Zuständigkeit des Aufrufers fallen auf den Stack gesichert werden. Diese können sein: RBX, RBP und R12 bis R15. Nun kann mit der Subroutine begonnen werden.
3. Der Rückgabewert der Subroutine muss in das Register RAX geschrieben werden.
4. Eventuell veränderte Register müssen mit den Sicherungen aus 2. Wiederhergestellt werden.
5. Lokale Variablen müssen deallokiert werden, in dem der Stackpointer wieder auf Ursprungswert zurückgesetzt wird.
6. Zurückkehren zum Aufrufer durch eine ret Anweisung. Diese poppt die Rückkehraddresse vom Stack.
