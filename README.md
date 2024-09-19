# RPG Konsolenspiel

Dies ist ein einfaches RPG-Spiel, das in C++ erstellt wurde. Das Spiel bietet dem Spieler die Möglichkeit, eine Klasse zu wählen, gegen zufällige Gegner zu kämpfen, Fähigkeiten zu verbessern und Erfahrungspunkte zu sammeln, um im Level aufzusteigen.

## Spielübersicht

Der Spieler kann eine von drei Klassen wählen:
- **Krieger**
- **Magier**
- **Bogenschütze**

Jede Klasse hat einzigartige Fähigkeiten und kann Tränke (Heiltränke, Manatränke) im Spiel verwenden. Der Spieler kämpft gegen zufällige Gegner, die ebenfalls verschiedene Gegenstände und Tränke fallen lassen können. 

### Funktionen
- **Klassenwahl**: Der Spieler wählt am Anfang eine Klasse aus.
- **Kampfsystem**: Der Spieler kann Gegner angreifen, Fähigkeiten einsetzen und sich heilen.
- **Regeneration**: Der Spieler regeneriert HP und Mana außerhalb des Kampfes.
- **Level-Up-System**: Der Spieler erhält Erfahrungspunkte (XP) durch das Besiegen von Gegnern und kann im Level aufsteigen, wodurch HP und Mana erhöht werden.
- **Inventar**: Der Spieler kann verschiedene Gegenstände und Tränke sammeln und verwenden.
- **Speichern und Laden**: Der Spieler kann den Fortschritt im Spiel speichern und später wieder laden.

## Installationsanweisungen

1. **Klonen des Repositories**:
   ```bash
   git clone https://github.com/kruemmel-python/rpgtest.git
   ```
2. **Öffnen des Projekts in Visual Studio**: Das Spiel wurde mit Visual Studio entwickelt und kann dort geöffnet und kompiliert werden.
3. **Compilieren und Ausführen**:
   - Öffne die Projektdatei `rpgtest.sln` in Visual Studio.
   - Führe das Projekt über Visual Studio aus oder kompiliere und führe es manuell über die Kommandozeile mit einem C++-Compiler.

## Spielsteuerung

- Das Spiel wird über das Konsolenfenster gesteuert.
- Der Spieler wird durch Menüs navigiert und gibt die Nummer der gewünschten Aktion ein.
- Aktionen im Spiel:
  - **1**: Statistiken anzeigen (zeigt HP, Mana, Level und XP).
  - **2**: Fähigkeiten anzeigen.
  - **3**: Fähigkeit verbessern.
  - **4**: Inventar anzeigen.
  - **5**: Abenteuer fortsetzen (dies startet einen Kampf mit einem zufälligen Gegner).
  - **6**: Spiel speichern.
  - **7**: Spiel beenden.

## Beispiel für das Spiel

```bash
Möchtest du ein neues Spiel starten oder ein gespeichertes Spiel laden?
1. Neues Spiel
2. Spiel laden

Wähle deine Klasse: Krieger, Magier, Bogenschütze: Krieger

Was möchtest du tun?
1. Statistiken anzeigen
2. Fähigkeiten anzeigen
3. Fähigkeit verbessern
4. Inventar anzeigen
5. Abenteuer fortsetzen
6. Spiel speichern
7. Spiel beenden
```

### Beispiel für einen Kampf:

```bash
Du triffst auf einen Goblin!
Kampf gegen Goblin beginnt!

Was möchtest du tun?
1. Angreifen
2. Fähigkeit einsetzen
3. Heilen
4. Info Gegner
```

## Dateien

- `main.cpp`: Die Hauptdatei des Spiels, die die Spielmechanik implementiert.
- `items.csv`: Eine CSV-Datei mit einer Liste von zufälligen Gegenständen und Tränken, die von Gegnern fallen gelassen werden.
- `saved_game.txt`: Eine Textdatei, in der der Spielfortschritt gespeichert wird.

## Erweiterungsmöglichkeiten

- **Neue Klassen**: Füge weitere Klassen wie Paladin oder Assassine hinzu.
- **Mehr Fähigkeiten**: Erweitere die Fähigkeiten jeder Klasse.
- **Mehr Gegner**: Implementiere zusätzliche Gegner mit unterschiedlichen Eigenschaften.
- **Komplexere Storyline**: Füge eine Story hinzu, die den Spieler durch verschiedene Quests führt.

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz. Siehe die `LICENSE`-Datei für weitere Details.

