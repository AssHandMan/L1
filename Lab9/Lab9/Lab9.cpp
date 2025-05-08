#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <memory>
#include <algorithm>

class Character {
private:
    std::string name;
    int hp, maxHp, attack, defense, level, exp;

public:
    Character(std::string n = "Hero") : name(n), hp(100), maxHp(100), attack(10), defense(5), level(1), exp(0) {}

    Character(std::string n, int hp_, int atk_, int def_, int maxHp_, int lvl_, int exp_)
        : name(n), hp(hp_), attack(atk_), defense(def_), maxHp(maxHp_), level(lvl_), exp(exp_) {}

    void showInfo() const {
        std::cout << name << " - HP: " << hp << "/" << maxHp << " | ATK: " << attack
            << " | DEF: " << defense << " | LVL: " << level << " | EXP: " << exp << "\n";
    }

    void gainExp(int amount) {
        exp += amount;
        if (exp >= level * 10) {
            exp -= level * 10;
            level++;
            std::cout << "Level up! Now level " << level << "!\n";
            increaseRandomStat();
        }
    }

    void heal() {
        restoreHP(20);
        std::cout << name << " healed for 20 HP.\n";
    }

    void takeDamage(int dmg) {
        int damage = dmg - defense;
        if (damage < 0) damage = 0;
        hp -= damage;
        std::cout << name << " takes " << damage << " damage.\n";
    }

    void restoreHP(int amount) {
        hp += amount;
        if (hp > maxHp) hp = maxHp;
    }

    bool isAlive() const { return hp > 0; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getHP() const { return hp; }
    std::string getName() const { return name; }

    void increaseRandomStat() {
        int choice = rand() % 3;
        switch (choice) {
        case 0: attack += 2; std::cout << "Attack increased!\n"; break;
        case 1: defense += 2; std::cout << "Defense increased!\n"; break;
        case 2: maxHp += 10; hp += 10; std::cout << "HP increased!\n"; break;
        }
    }

    void status() const {
        std::cout << "Character Status:\n";
        showInfo();
    }

    int getMaxHP() const { return maxHp; }
    int getLevel() const { return level; }
    int getExp() const { return exp; }
};

template<typename T>
class Inventory {
private:
    std::vector<T> items;

public:
    void addItem(const T& item) {
        items.push_back(item);
    }

    void removeItem(const T& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) items.erase(it);
    }

    bool contains(const T& item) const {
        return std::find(items.begin(), items.end(), item) != items.end();
    }

    void showInventory() const {
        std::cout << "Inventory:\n";
        if (items.empty()) std::cout << "  (empty)\n";
        for (const auto& item : items) std::cout << "  - " << item << "\n";
    }
};

class Monster {
protected:
    std::string name;
    int hp, attack, defense;

public:
    Monster(std::string n, int h, int a, int d) : name(n), hp(h), attack(a), defense(d) {}
    virtual ~Monster() = default;

    virtual void showInfo() const {
        std::cout << name << " - HP: " << hp << ", ATK: " << attack << ", DEF: " << defense << "\n";
    }

    virtual void takeDamage(int dmg) {
        int damage = dmg - defense;
        if (damage < 0) damage = 0;
        hp -= damage;
        std::cout << name << " takes " << damage << " damage.\n";
    }

    bool isAlive() const { return hp > 0; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    std::string getName() const { return name; }
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 30, 5, 2) {}
};

class Skeleton : public Monster {
public:
    Skeleton() : Monster("Skeleton", 40, 7, 3) {}
};

class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 100, 15, 5) {}
};

class Game {
private:
    Character player;
    Inventory<std::string> inventory;
    int x = 0, y = 0;

    std::unique_ptr<Monster> spawnMonster() {
        int r = rand() % 3;
        if (r == 0) return std::make_unique<Goblin>();
        if (r == 1) return std::make_unique<Skeleton>();
        return std::make_unique<Dragon>();
    }

    void battle(std::unique_ptr<Monster> monster) {
        while (player.isAlive() && monster->isAlive()) {
            std::cout << "\n";
            player.showInfo();
            monster->showInfo();

            std::cout << "Attack or run? ";
            std::string action;
            std::cin >> action;

            if (action == "run") {
                std::cout << "You escaped!\n";
                return;
            }

            monster->takeDamage(player.getAttack());
            if (!monster->isAlive()) break;
            player.takeDamage(monster->getAttack());
        }

        if (player.isAlive()) {
            std::cout << "You defeated the " << monster->getName() << "!\n";
            player.gainExp(5 + rand() % 6);
            player.increaseRandomStat();
            inventory.addItem("Healing Potion");
        }
    }

    void saveGame() {
        std::ofstream out("save.txt");
        if (!out) {
            std::cerr << "Failed to save game.\n";
            return;
        }

        out << x << " " << y << "\n";
        out << player.getName() << "\n";
        out << player.getHP() << " " << player.getAttack() << " " << player.getDefense() << " "
            << player.getMaxHP() << " " << player.getLevel() << " " << player.getExp() << "\n";
        out << inventory.contains("Healing Potion") << " " << inventory.contains("Sword") << "\n";
        std::cout << "Game saved.\n";
    }

    void loadGame() {
        std::ifstream in("save.txt");
        if (!in) {
            std::cerr << "Failed to load game.\n";
            return;
        }

        int hp, atk, def, maxHp, lvl, exp;
        std::string name;
        int hasPotion, hasSword;
        in >> x >> y;
        in.ignore();
        std::getline(in, name);
        in >> hp >> atk >> def >> maxHp >> lvl >> exp;
        in >> hasPotion >> hasSword;

        player = Character(name, hp, atk, def, maxHp, lvl, exp);
        inventory = Inventory<std::string>();
        if (hasPotion) inventory.addItem("Healing Potion");
        if (hasSword) inventory.addItem("Sword");

        std::cout << "Game loaded.\n";
        player.status();
    }

    void processAction() {
        std::string cmd;
        std::cout << "> ";
        std::cin >> cmd;

        if (cmd == "move") {
            std::string dir;
            std::cin >> dir;
            if (dir == "up") y++;
            else if (dir == "down") y--;
            else if (dir == "left") x--;
            else if (dir == "right") x++;
            else {
                std::cout << "Unknown direction.\n";
                return;
            }

            std::cout << "You moved to (" << x << "," << y << ").\n";
            player.gainExp(1);

            if (rand() % 3 == 0) {
                std::cout << "A monster appears!\n";
                auto monster = spawnMonster();
                battle(std::move(monster));
            }

        }
        else if (cmd == "heal") {
            if (inventory.contains("Healing Potion")) {
                player.heal();
                inventory.removeItem("Healing Potion");
            }
            else {
                std::cout << "No potions left!\n";
            }

        }
        else if (cmd == "inventory") {
            inventory.showInventory();

        }
        else if (cmd == "save") {
            saveGame();

        }
        else if (cmd == "load") {
            loadGame();

        }
        else if (cmd == "status") {
            player.status();

        }
        else if (cmd == "quit") {
            exit(0);

        }
        else {
            std::cout << "Unknown command.\n";
        }
    }

public:
    void start() {
        std::cout << "Load game or new game? (load/new): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "load") {
            loadGame();
        }
        else {
            std::cout << "Enter your character's name: ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            player = Character(name);
            inventory.addItem("Healing Potion");
            inventory.addItem("Sword");
        }

        std::cout << "Game started. Commands: move [dir], heal, inventory, save, load, status, quit\n";

        while (true) {
            processAction();
            if (!player.isAlive()) {
                std::cout << "You died. Game over.\n";
                break;
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Game game;
    game.start();
    return 0;
}
