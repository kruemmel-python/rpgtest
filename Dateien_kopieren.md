Um sicherzustellen, dass Dateien wie **items.csv** und **saved_game.txt** in den **Debug**- und **Release**-Ordnern gespeichert werden und somit von deinem Programm verwendet werden können, musst du in **Visual Studio** bestimmte Schritte ausführen. Hier ist eine Erklärung, wie dies anhand der bereitgestellten Screenshots zu erreichen ist:
### Schritte zur Konfiguration:

1. **Dateien zum Projekt hinzufügen**:
   - Im **Projektmappen-Explorer** (Bild 1) kannst du sehen, dass die Dateien **items.csv** und **saved_game.txt** bereits dem Projekt hinzugefügt wurden. Das ist der erste wichtige Schritt. Falls sie noch nicht hinzugefügt sind, klicke mit der rechten Maustaste auf das Projekt und wähle **Hinzufügen > Vorhandenes Element**, um die Dateien hinzuzufügen.

![image](https://github.com/user-attachments/assets/403c5d74-8364-4e7a-8b08-2062a09c8e4c)

2. **Eigenschaften der Dateien öffnen**:
   - Klicke mit der rechten Maustaste auf die hinzugefügten Dateien (z. B. **items.csv**), um das **Eigenschaftsfenster** zu öffnen. (Siehe Bild oben)

2. **Eigenschaften der Dateien öffnen**:
   - Klicke mit der rechten Maustaste auf die hinzugefügten Dateien (z. B. **items.csv**), um das **Eigenschaftsfenster** zu öffnen. (Siehe Bild oben)

![image](https://github.com/user-attachments/assets/d490ab9a-9f5b-443a-9f26-8ad22c6b5c11)
3. **Inhalt als Kopierdatei festlegen**:
   - Im Eigenschaftsfenster der Datei unter **Allgemein** (Bild 2) kannst du sicherstellen, dass die Datei **Vom Build ausgeschlossen** auf **Nein** gesetzt ist. Dies bedeutet, dass die Datei im Build enthalten ist.
   - Stelle unter **Elementtyp** sicher, dass **Datei kopieren** ausgewählt ist, um festzulegen, dass die Datei kopiert wird.

![image](https://github.com/user-attachments/assets/b613117d-e5b9-40e2-9142-c923c2db823f)
4. **Zielverzeichnis konfigurieren**:
   - Gehe auf den Reiter **Datei kopieren** im Eigenschaftsfenster (Bild 3). Hier kannst du das Zielverzeichnis einstellen, in dem die Datei nach dem Kompilieren abgelegt wird. 
   - Der Wert **$(OutDir)** gibt an, dass die Datei im Ausgabeordner (Debug oder Release) abgelegt wird. Du kannst den Namen der Zieldatei ebenfalls anpassen, falls nötig.
   - Setze **Zieldateien als Inhalt behandeln** auf **Ja**, um sicherzustellen, dass die Datei bereitgestellt wird.

![image](https://github.com/user-attachments/assets/ea6a9c75-0b5a-4b4a-ba03-6de0558c19d7)

![image](https://github.com/user-attachments/assets/e275fa5a-a1f1-4ac6-bbc4-538c15856569)


5. **Dateien im Ausgabeordner überprüfen**:
   - Nach dem Kompilieren findest du die **items.csv** und **saved_game.txt** im entsprechenden **Debug**- oder **Release**-Ordner (siehe Bild 4 und Bild 5). Hier siehst du, dass die Dateien erfolgreich in den **Release**-Ordner kopiert wurden.


### Ergebnis:
Mit diesen Einstellungen werden die Dateien **items.csv** und **saved_game.txt** nach jedem Build automatisch in den entsprechenden Ordner kopiert, sodass das Programm darauf zugreifen kann, egal ob es im Debug- oder Release-Modus ausgeführt wird.
