# RPG Konsolenspiel

Dies ist ein einfaches RPG-Spiel, das in C++ erstellt wurde. Das Spiel bietet dem Spieler die M�glichkeit, eine Klasse zu w�hlen, gegen zuf�llige Gegner zu k�mpfen, F�higkeiten zu verbessern und Erfahrungspunkte zu sammeln, um im Level aufzusteigen.

## Spiel�bersicht

Der Spieler kann eine von drei Klassen w�hlen:
- **Krieger**
- **Magier**
- **Bogensch�tze**

Jede Klasse hat einzigartige F�higkeiten und kann Tr�nke (Heiltr�nke, Manatr�nke) im Spiel verwenden. Der Spieler k�mpft gegen zuf�llige Gegner, die ebenfalls verschiedene Gegenst�nde und Tr�nke fallen lassen k�nnen. 

### Funktionen
- **Klassenwahl**: Der Spieler w�hlt am Anfang eine Klasse aus.
- **Kampfsystem**: Der Spieler kann Gegner angreifen, F�higkeiten einsetzen und sich heilen.
- **Regeneration**: Der Spieler regeneriert HP und Mana au�erhalb des Kampfes.
- **Level-Up-System**: Der Spieler erh�lt Erfahrungspunkte (XP) durch das Besiegen von Gegnern und kann im Level aufsteigen, wodurch HP und Mana erh�ht werden.
- **Inventar**: Der Spieler kann verschiedene Gegenst�nde und Tr�nke sammeln und verwenden.
- **Speichern und Laden**: Der Spieler kann den Fortschritt im Spiel speichern und sp�ter wieder laden.

## Installationsanweisungen

1. **Klonen des Repositories**:
   ```bash
   git clone https://github.com/Benutzername/rpgtest.git
   ```
2. **�ffnen des Projekts in Visual Studio**: Das Spiel wurde mit Visual Studio entwickelt und kann dort ge�ffnet und kompiliert werden.
3. **Compilieren und Ausf�hren**:
   - �ffne die Projektdatei `rpgtest.sln` in Visual Studio.
   - F�hre das Projekt �ber Visual Studio aus oder kompiliere und f�hre es manuell �ber die Kommandozeile mit einem C++-Compiler.

## Spielsteuerung

- Das Spiel wird �ber das Konsolenfenster gesteuert.
- Der Spieler wird durch Men�s navigiert und gibt die Nummer der gew�nschten Aktion ein.
- Aktionen im Spiel:
  - **1**: Statistiken anzeigen (zeigt HP, Mana, Level und XP).
  - **2**: F�higkeiten anzeigen.
  - **3**: F�higkeit verbessern.
  - **4**: Inventar anzeigen.
  - **5**: Abenteuer fortsetzen (dies startet einen Kampf mit einem zuf�lligen Gegner).
  - **6**: Spiel speichern.
  - **7**: Spiel beenden.

## Beispiel f�r das Spiel

```bash
M�chtest du ein neues Spiel starten oder ein gespeichertes Spiel laden?
1. Neues Spiel
2. Spiel laden

W�hle deine Klasse: Krieger, Magier, Bogensch�tze: Krieger

Was m�chtest du tun?
1. Statistiken anzeigen
2. F�higkeiten anzeigen
3. F�higkeit verbessern
4. Inventar anzeigen
5. Abenteuer fortsetzen
6. Spiel speichern
7. Spiel beenden
```

### Beispiel f�r einen Kampf:

```bash
Du triffst auf einen Goblin!
Kampf gegen Goblin beginnt!

Was m�chtest du tun?
1. Angreifen
2. F�higkeit einsetzen
3. Heilen
4. Info Gegner
```

## Dateien

- `main.cpp`: Die Hauptdatei des Spiels, die die Spielmechanik implementiert.
- `items.csv`: Eine CSV-Datei mit einer Liste von zuf�lligen Gegenst�nden und Tr�nken, die von Gegnern fallen gelassen werden.
- `saved_game.txt`: Eine Textdatei, in der der Spielfortschritt gespeichert wird.

## Erweiterungsm�glichkeiten

- **Neue Klassen**: F�ge weitere Klassen wie Paladin oder Assassine hinzu.
- **Mehr F�higkeiten**: Erweitere die F�higkeiten jeder Klasse.
- **Mehr Gegner**: Implementiere zus�tzliche Gegner mit unterschiedlichen Eigenschaften.
- **Komplexere Storyline**: F�ge eine Story hinzu, die den Spieler durch verschiedene Quests f�hrt.

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz. Siehe die `LICENSE`-Datei f�r weitere Details.

