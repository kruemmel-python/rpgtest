#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>  // F�r das Lesen und Schreiben von Dateien
#include <random>   // F�r zuf�llige Auswahl von Gegenst�nden und Gegnern
#include <ctime>
#include <clocale>  // F�r setlocale()
#include <windows.h> // F�r Sleep()
#include <sstream>  // Hinzuf�gen dieser Zeile f�r std::istringstream

// Funktion zur Umwandlung von Gro�- in Kleinbuchstaben
std::string to_lowercase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Funktion zum Laden der Items aus einer CSV-Datei
std::pair<std::string, std::string> loadRandomItemsFromCSV(const std::string& filename) {
    std::vector<std::pair<std::string, std::string>> items;
    std::ifstream file(filename);
    std::string line;

    // Spaltennamen �berspringen
    std::getline(file, line);

    // Lesen der Gegenst�nde aus der CSV-Datei
    while (std::getline(file, line)) {
        std::size_t commaPos = line.find(',');
        std::string item = line.substr(0, commaPos);
        std::string trank = line.substr(commaPos + 1);
        items.emplace_back(item, trank);
    }

    // Zuf�llige Auswahl eines Gegenstands und eines Tranks
    std::srand(std::time(0));
    int randomIndex = std::rand() % items.size();
    return items[randomIndex];
}

// Gegnerklasse
class Enemy {
public:
    std::string name;
    int hp;
    int xpReward;
    int attackPower;
    std::string itemDrop;
    std::string potionDrop;

    Enemy(std::string n, int h, int xp, int ap, std::pair<std::string, std::string> drops)
        : name(n), hp(h), xpReward(xp), attackPower(ap), itemDrop(drops.first), potionDrop(drops.second) {}

    void takeDamage(int damage) {
        hp -= damage;
        if (hp <= 0) {
            std::cout << name << " wurde besiegt!\n";
        }
        else {
            std::cout << name << " hat noch " << hp << " HP �brig.\n";
        }
    }

    bool isAlive() const {
        return hp > 0;
    }

    void attackPlayer(int& playerHP, int defenseBoost) {
        int actualDamage = attackPower - defenseBoost;
        if (actualDamage < 0) actualDamage = 0;  // Verhindere negativen Schaden
        std::cout << name << " greift den Spieler mit " << actualDamage << " Schaden an!\n";
        playerHP -= actualDamage;
        if (playerHP <= 0) {
            std::cout << "Du wurdest besiegt!\n";
        }
        else {
            std::cout << "Du hast noch " << playerHP << " HP �brig.\n";
        }
    }

    // Neue Methode zur Anzeige der Gegnerinformationen
    void showInfo() const {
        std::cout << "\n*** Gegnerinformationen ***\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "HP: " << hp << "\n";
        std::cout << "Angriffskraft: " << attackPower << "\n";
        std::cout << "XP Belohnung: " << xpReward << "\n";
        std::cout << "Item-Drop: " << itemDrop << "\n";
        std::cout << "Trank-Drop: " << potionDrop << "\n";
    }
};

// Spielerklasse
class Player {
public:
    // Spielerwerte
    std::string playerClass;
    int level;
    int hp;
    int maxHP;             // Maximale HP hinzugef�gt
    int xp;
    int mana;              // Mana hinzugef�gt
    int maxMana;           // Maximales Mana hinzugef�gt
    int abilityPoints;
    int xpForNextLevel;
    int defenseBoost;

    // Inventar
    std::unordered_map<std::string, int> inventory;
    std::unordered_map<std::string, int> abilities;

    // Konstruktor f�r die Spielerklasse
    Player(std::string chosenClass) {
        playerClass = chosenClass;
        level = 1;
        maxHP = 100;        // Maximale HP auf 100 gesetzt
        hp = maxHP;         // Startet mit vollen HP
        xp = 0;
        mana = 100;         // Startmana auf 100 gesetzt
        maxMana = 100;      // Maximales Mana auf 100 gesetzt
        abilityPoints = 2;
        xpForNextLevel = 100;
        defenseBoost = 0;

        // Initiales Inventar mit Manatrank
        inventory = { {"Heiltrank", 1}, {"Manatrank", 1}, {"Schwert", 1} };

        // F�higkeiten mit Mana-Kosten, speziell f�r Magier
        if (chosenClass == "magier") {
            abilities = { {"feuerball", 10}, {"heilung", 8}, {"blitzschlag", 7}, {"teleport", 5}, {"magische barriere", 9} };
        }
        else if (chosenClass == "krieger") {
            abilities = { {"schwertkampf", 10}, {"verteidigung", 10}, {"wut", 5}, {"schildschlag", 8}, {"kampfkunst", 7} };
        }
        else if (chosenClass == "bogenschuetze") {
            abilities = { {"pfeilschuss", 10}, {"ausweichen", 7}, {"fallenstellen", 5}, {"mehrfachschuss", 8}, {"tarnung", 9} };
        }
    }

    // Methode zum Verwenden eines Manatranks
    void useManaPotion() {
        if (inventory["Manatrank"] > 0) {
            mana += 30;
            if (mana > maxMana) mana = maxMana;  // Mana darf das Maximum nicht �berschreiten
            inventory["Manatrank"]--;
            std::cout << "Du hast einen Manatrank benutzt. Dein Mana betr�gt jetzt: " << mana << "/" << maxMana << "\n";
        }
        else {
            std::cout << "Du hast keinen Manatrank mehr!\n";
        }
    }

    // F�higkeit nutzen, wobei Mana verbraucht wird
    void useAbility(Enemy& enemy) {
        std::cout << "\nW�hle eine F�higkeit:\n";
        int i = 1;
        std::unordered_map<int, std::string> abilityOptions;
        for (const auto& ability : abilities) {
            std::cout << i << ". " << ability.first << " (Schaden: " << ability.second << ")\n";
            abilityOptions[i] = ability.first;
            i++;
        }

        int abilityChoice;
        std::cin >> abilityChoice;

        if (abilityOptions.find(abilityChoice) != abilityOptions.end()) {
            std::string chosenAbility = abilityOptions[abilityChoice];

            int manaKosten = abilities[chosenAbility];  // Annahme: Mana-Kosten entsprechen dem F�higkeitswert
            if (mana >= manaKosten) {
                mana -= manaKosten;  // Mana wird abgezogen
                std::cout << "Du setzt " << chosenAbility << " ein und hast jetzt " << mana << " Mana �brig.\n";
                int abilityPower = abilities[chosenAbility];
                enemy.takeDamage(abilityPower);
            }
            else {
                std::cout << "Nicht genug Mana, um " << chosenAbility << " zu verwenden!\n";
            }
        }
    }

    // Mana-Regeneration au�erhalb des Kampfes
    void regenerateMana() {
        int previousMana = mana; // Speichern des vorherigen Mana-Werts
        if (mana < maxMana) {
            mana += 5;  // Regeneriere 5 Mana pro Aufruf
            if (mana > maxMana) {
                mana = maxMana;  // Sicherstellen, dass das Mana nicht �ber das Maximum hinausgeht
            }
        }
        // Zeige nur eine Nachricht, wenn das Mana tats�chlich erh�ht wurde
        if (mana != previousMana) {
            std::cout << "Mana regeneriert. Aktuelles Mana: " << mana << "/" << maxMana << "\n";
        }
    }

    // HP-Regeneration au�erhalb des Kampfes
    void regenerateHP() {
        int previousHP = hp;  // Speichere den vorherigen HP-Wert

        if (hp < maxHP) {
            hp += 5;  // Regeneriere 5 HP pro Aufruf
            if (hp > maxHP) {
                hp = maxHP;  // Stelle sicher, dass HP nicht �ber das Maximum hinausgehen
            }
        }
        // Zeige nur eine Nachricht, wenn die HP tats�chlich erh�ht wurden
        if (hp != previousHP) {
            std::cout << "HP regeneriert. Aktuelle HP: " << hp << "/" << maxHP << "\n";
        }
    }

    // F�higkeiten aufleveln
    void upgradeAbility(const std::string& abilityName, int points) {
        std::string lowerAbility = to_lowercase(abilityName);
        if (abilities.find(lowerAbility) != abilities.end() && points <= abilityPoints) {
            abilities[lowerAbility] += points;
            abilityPoints -= points;
            std::cout << lowerAbility << " wurde um " << points << " Punkte verbessert.\n";
        }
    }

    // XP sammeln und Level aufsteigen
    void gainXP(int gainedXP) {
        xp += gainedXP;
        std::cout << "Du hast " << gainedXP << " XP erhalten. Aktuelle XP: " << xp << "/" << xpForNextLevel << "\n";
        if (xp >= xpForNextLevel) {
            xp -= xpForNextLevel;
            levelUp();
        }
    }

    // Level aufsteigen
    void levelUp() {
        level++;
        maxHP += 20;         // MaxHP wird pro Level um 20 erh�ht
        hp = maxHP;          // Aktuelle HP auf das neue Maximum setzen
        abilityPoints += 2;
        mana += 10;          // Mana erh�ht
        xpForNextLevel += 50;
        std::cout << "\n*** Gl�ckwunsch! Du bist auf Level " << level << " aufgestiegen! ***\n";
        std::cout << "Dein maximales HP betr�gt jetzt: " << maxHP << "\n";
    }

    // Inventar anzeigen
    void showInventory() {
        std::cout << "\nDein Inventar:\n";
        for (const auto& item : inventory) {
            std::cout << "- " << item.first << " (Menge: " << item.second << ")\n";
        }
    }

    // F�higkeiten anzeigen
    void showAbilities() {
        std::cout << "\nDeine F�higkeiten:\n";
        for (const auto& ability : abilities) {
            std::cout << ability.first << ": " << ability.second << std::endl;
        }
        std::cout << "Verf�gbare F�higkeitspunkte: " << abilityPoints << std::endl;
    }

    // Statistiken anzeigen
    void showStats() {
        std::cout << "\n*** Spielerstatistiken ***\n";
        std::cout << "Klasse: " << playerClass << "\nLevel: " << level << "\nHP: " << hp << "/" << maxHP << "\nXP: " << xp << "/" << xpForNextLevel << "\nMana: " << mana << "/" << maxMana << std::endl;
    }

    // Heiltrank verwenden
    void heal() {
        if (inventory["Heiltrank"] > 0) {
            hp += 30;
            if (hp > maxHP) hp = maxHP;  // HP darf das Maximum nicht �berschreiten
            inventory["Heiltrank"]--;
            std::cout << "Du verwendest einen Heiltrank und erh�hst deine HP um 30. Aktuelle HP: " << hp << " (Heiltr�nke �brig: " << inventory["Heiltrank"] << ")\n";
        }
        else {
            std::cout << "Du hast keinen Heiltrank im Inventar!\n";
        }
    }

    // Gegner angreifen
    void attackEnemy(Enemy& enemy) {
        int attackPower = 10 + (level * 2);
        std::cout << "Du greifst " << enemy.name << " mit " << attackPower << " Schaden an.\n";
        enemy.takeDamage(attackPower);
    }

    // Gegenstand ins Inventar hinzuf�gen (Menge erh�hen, wenn der Gegenstand bereits existiert)
    void addItemToInventory(const std::string& item) {
        if (inventory.find(item) != inventory.end()) {
            inventory[item]++;
        }
        else {
            inventory[item] = 1;
        }
        std::cout << item << " wurde zu deinem Inventar hinzugef�gt! (Menge: " << inventory[item] << ")\n";
    }

    // Spiel speichern
    void saveGame(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Fehler beim �ffnen der Datei zum Speichern!\n";
            return;
        }

        file << playerClass << "\n";
        file << level << "\n";
        file << hp << "\n";
        file << maxHP << "\n";   // Speichern von maxHP
        file << xp << "\n";
        file << mana << "\n";
        file << maxMana << "\n";  // Maximales Mana wird ebenfalls gespeichert
        file << abilityPoints << "\n";
        file << xpForNextLevel << "\n";
        file << defenseBoost << "\n";  // Verteidigungsboost wird gespeichert

        // Speichern des Inventars
        file << "INVENTORY\n";
        for (const auto& item : inventory) {
            file << item.first << " " << item.second << "\n";
        }

        // Speichern der F�higkeiten
        file << "ABILITIES\n";
        for (const auto& ability : abilities) {
            file << ability.first << " " << ability.second << "\n";
        }

        file.close();
        std::cout << "Spiel erfolgreich gespeichert!\n";
    }

    // Spiel laden
    void loadGame(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Fehler: Spielstand konnte nicht geladen werden.\n";
            return;
        }

        std::getline(file, playerClass);
        file >> level >> hp >> maxHP >> xp >> mana >> maxMana >> abilityPoints >> xpForNextLevel >> defenseBoost;
        file.ignore();  // Zum Ignorieren des Newlines nach defenseBoost

        std::string section;

        // Abschnitt INVENTORY lesen
        std::getline(file, section);
        if (section == "INVENTORY") {
            inventory.clear();
            while (std::getline(file, section)) {
                if (section == "ABILITIES") {
                    break;  // Inventarabschnitt ist fertig, nun zu den F�higkeiten
                }
                std::istringstream inventoryStream(section);
                std::string itemName;
                int itemCount;
                inventoryStream >> itemName >> itemCount;
                inventory[itemName] = itemCount;
            }
        }

        // Abschnitt ABILITIES lesen
        abilities.clear();
        while (std::getline(file, section)) {
            std::istringstream abilityStream(section);
            std::string abilityName;
            int abilityValue;
            if (abilityStream >> abilityName >> abilityValue) {
                abilities[abilityName] = abilityValue;
            }
        }

        file.close();
        std::cout << "Spiel erfolgreich geladen!\n";
    }
};


// Funktion zur Darstellung der "Abenteuer fortsetzen"-Bewegung
#include <iostream>
#include <chrono>
#include <thread>

// Funktion zur Darstellung der rotierenden Zeichen
void simulateJourney() {
    std::cout << "\nDu setzt dein Abenteuer fort...\n";

    // Array mit den Rotationszeichen
    char rotation[] = { '|', '/', '-', '\\' };

    // 12 Wiederholungen der Animation (entspricht 3 Umdrehungen)
    for (int i = 0; i < 12; ++i) {
        // Ausgabe des aktuellen Rotationszeichens
        std::cout << rotation[i % 4] << "\r";  // \r kehrt zum Anfang der Zeile zur�ck
        std::cout.flush();  // Zwingt die Konsole, die Ausgabe sofort anzuzeigen

        // Wartezeit von 200ms
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Abschluss der Animation
    std::cout << "Du triffst auf einen Gegner!\n";
}

// Funktion zum Erstellen eines zuf�lligen Gegners
Enemy generateRandomEnemy() {
    std::vector<std::string> enemyNames = { "Goblin", "Orc", "Troll", "Bandit", "Drachenling" };
    std::srand(std::time(0));
    std::string randomName = enemyNames[std::rand() % enemyNames.size()];
    int randomHP = 20 + std::rand() % 100;  // HP zwischen 20 und 120
    int randomXP = 10 + std::rand() % 50;   // XP zwischen 10 und 60
    int randomAttackPower = 5 + std::rand() % 15;  // Angriffskraft zwischen 5 und 20
    std::pair<std::string, std::string> drops = loadRandomItemsFromCSV("items.csv");

    return Enemy(randomName, randomHP, randomXP, randomAttackPower, drops);
}

// Kampfmechanik
void fight(Player& player, Enemy& enemy) {
    std::cout << "\nKampf gegen " << enemy.name << " beginnt!\n";
    while (player.hp > 0 && enemy.isAlive()) {
        std::cout << "\nWas m�chtest du tun?\n1. Angreifen\n2. F�higkeit einsetzen\n3. Heilen\n4. Info Gegner\n";
        int action;
        std::cin >> action;

        if (action == 1) {
            player.attackEnemy(enemy);
        }
        else if (action == 2) {
            player.useAbility(enemy);
        }
        else if (action == 3) {
            player.heal();
        }
        // Neue Option, um Gegnerinformationen anzuzeigen
        else if (action == 4) {
            enemy.showInfo();  // Zeigt die Informationen des Gegners an
        }
        else {
            std::cout << "Ung�ltige Aktion!\n";
            continue;
        }

        if (enemy.isAlive()) {
            enemy.attackPlayer(player.hp, player.defenseBoost);
        }
    }

    if (player.hp > 0) {
        std::cout << "Du hast " << enemy.name << " besiegt und " << enemy.xpReward << " XP erhalten!\n";
        player.gainXP(enemy.xpReward);
        player.addItemToInventory(enemy.itemDrop);
        player.addItemToInventory(enemy.potionDrop);
    }
}

// Funktion zur Spielerklassenauswahl
std::string chooseClass() {
    std::string chosenClass;
    std::cout << "W�hle deine Klasse: Krieger, Magier, Bogenschuetze: ";
    std::getline(std::cin, chosenClass);
    chosenClass = to_lowercase(chosenClass);

    if (chosenClass == "krieger" || chosenClass == "magier" || chosenClass == "bogenschuetze") {
        return chosenClass;
    }
    else {
        std::cout << "Ung�ltige Klasse, bitte w�hle erneut.\n";
        return chooseClass();
    }
}

int main() {
    setlocale(LC_ALL, "de_DE");  // Setzt das Locale auf Deutsch
    SetConsoleOutputCP(CP_UTF8);  // F�r UTF-8 Konsolenausgabe

    std::string playerClass;
    Player* player = nullptr;

    std::cout << "M�chtest du ein neues Spiel starten oder ein gespeichertes Spiel laden?\n";
    std::cout << "1. Neues Spiel\n2. Spiel laden\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore();  // Zum Ignorieren der Newline

    if (choice == 1) {
        playerClass = chooseClass();
        player = new Player(playerClass);
    }
    else if (choice == 2) {
        player = new Player("dummy");  // Tempor�r, um das Objekt zu erstellen
        player->loadGame("saved_game.txt");
    }
    else {
        std::cout << "Ung�ltige Auswahl.\n";
        return 0;
    }

    bool gameRunning = true;
    while (gameRunning) {
        // Regeneration von HP und Mana jedes Mal pr�fen, wenn das Hauptmen� aufgerufen wird
        player->regenerateHP();   // HP regenerieren
        player->regenerateMana(); // Mana regenerieren

        std::cout << "\nWas m�chtest du tun?\n1. Statistiken anzeigen\n2. F�higkeiten anzeigen\n3. F�higkeit verbessern\n4. Inventar anzeigen\n5. Abenteuer fortsetzen\n6. Spiel speichern\n7. Spiel beenden\n";
        int menuChoice;
        std::cin >> menuChoice;
        std::cin.ignore();

        if (menuChoice == 1) {
            player->showStats();
        }
        else if (menuChoice == 2) {
            player->showAbilities();
        }
        else if (menuChoice == 3) {
            player->showAbilities();
            std::cout << "Welche F�higkeit m�chtest du verbessern? ";
            std::string abilityName;
            std::getline(std::cin, abilityName);
            std::cout << "Wie viele Punkte m�chtest du vergeben? ";
            int points;
            std::cin >> points;
            std::cin.ignore();
            player->upgradeAbility(abilityName, points);
        }
        else if (menuChoice == 4) {
            player->showInventory();
        }
        else if (menuChoice == 5) {
            // Spieler bewegt sich in der Welt
            simulateJourney();

            // Zuf�lligen Gegner erstellen und Kampf starten
            Enemy randomEnemy = generateRandomEnemy();
            fight(*player, randomEnemy);
        }
        else if (menuChoice == 6) {
            player->saveGame("saved_game.txt");
        }
        else if (menuChoice == 7) {
            gameRunning = false;
        }
        else {
            std::cout << "Ung�ltige Auswahl!\n";
        }

        // F�ge eine kleine Verz�gerung hinzu, um die Schleife nicht zu schnell durchlaufen zu lassen
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    delete player;
    std::cout << "Spiel beendet.\n";
    return 0;
}

