#include <iostream>
#include <vector>
#include <string>

class Pokemon {
private:
    std::string name;
    std::string strength;
    std::string weakness;

public:
    Pokemon(const std::string& name, const std::string& strength, const std::string& weakness)
        : name(name), strength(strength), weakness(weakness) {}

    std::string getName() const {
        return name;
    }

    std::string getStrength() const {
        return strength;
    }

    std::string getWeakness() const {
        return weakness;
    }

    virtual void battleCry() {} // make it virtual
};

class Charmander : public Pokemon {
public:
    Charmander(const std::string& name)
        : Pokemon(name, "Fire", "Water") {}

    void battleCry() override {
        std::cout << "Charmander: Char-char!" << std::endl;
    }
};

class Squirtle : public Pokemon {
public:
    Squirtle(const std::string& name)
        : Pokemon(name, "Water", "Leaf") {}

    void battleCry() override {
        std::cout << "Squirtle: squirtle-squirtle!" << std::endl;
    }
};

class Bulbasaur : public Pokemon {
public:
    Bulbasaur(const std::string& name)
        : Pokemon(name, "Grass", "Fire") {}

    void battleCry() override {
        std::cout << "Bulbasaur: Bulba-Bulba!" << std::endl;
    }
};

class Trainer {
private:
    std::string name;
    std::vector<Pokemon*> belt;

public:
    Trainer(const std::string& n)
        : name(n) {}

    ~Trainer() {
        for (Pokemon* pokemon : belt) {
            delete pokemon;
        }
    }

    void addPokemon(Pokemon* pokemon) {
        belt.push_back(pokemon);
    }

    Pokemon* throwPokeball() const {
        int index = rand() % belt.size();
        Pokemon* pokemon = belt[index];
        std::cout << name << ", I choose you, " << pokemon->getName() << "!" << std::endl;
        pokemon->battleCry();
        return pokemon;
    }

    void returnPokemon(Pokemon* pokemon) const {
        std::cout << name << ", rest well, " << pokemon->getName() << "!" << std::endl;
        pokemon->battleCry();
    }

    int getNumPokeballs() const {
        return belt.size();
    }

    std::string getName() const {
        return name;
    }
};

class Battle {
private:
    Trainer* trainer1;
    Trainer* trainer2;

public:
    Battle(Trainer* t1, Trainer* t2)
        : trainer1(t1), trainer2(t2) {}

    void fight() {
        std::cout << "Battle starts!" << std::endl;

        Pokemon* pokemon1 = trainer1->throwPokeball();
        Pokemon* pokemon2 = trainer2->throwPokeball();

        std::string strength1 = pokemon1->getStrength();
        std::string strength2 = pokemon2->getStrength();
        std::string weakness1 = pokemon1->getWeakness();
        std::string weakness2 = pokemon2->getWeakness();

        if (strength1 == weakness2 && strength2 == weakness1) {
            // Draw
            std::cout << "It's a draw!" << std::endl;
            trainer1->returnPokemon(pokemon1);
            trainer2->returnPokemon(pokemon2);
        }
        else if (strength1 == weakness2) {
            // Trainer 1 wins
            std::cout << trainer1->getName() << " wins the round!" << std::endl;
            trainer2->returnPokemon(pokemon2);
        }
        else if (strength2 == weakness1) {
            // Trainer 2 wins
            std::cout << trainer2->getName() << " wins the round!" << std::endl;
            trainer1->returnPokemon(pokemon1);
        }

        std::cout << "Round ends!" << std::endl;
    }
};

class Arena {
private:
    int totalRounds;
    int totalBattles;

public:
    Arena() : totalRounds(0), totalBattles(0) {}

    void startBattle(Trainer* trainer1, Trainer* trainer2) {
        Battle battle(trainer1, trainer2);
        battle.fight();
        totalRounds++;
        totalBattles++;
    }

    void displayScoreboard() const {
        std::cout << "Scoreboard" << std::endl;
        std::cout << "Total Rounds: " << totalRounds << std::endl;
        std::cout << "Total Battles: " << totalBattles << std::endl;
    }

    void resetScoreboard() {
        totalRounds = 0;
        totalBattles = 0;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    Arena arena;

    std::cout << "Enter the name of Trainer 1: ";
    std::string trainer1Name;
    std::getline(std::cin, trainer1Name);
    Trainer challengerOne(trainer1Name);

    std::cout << "Enter the name of Trainer 2: ";
    std::string trainer2Name;
    std::getline(std::cin, trainer2Name);
    Trainer opponentOne(trainer2Name);

    challengerOne.addPokemon(new Squirtle("Squirtle"));
    challengerOne.addPokemon(new Bulbasaur("Bulbasaur"));
    challengerOne.addPokemon(new Charmander("Charmander"));

    opponentOne.addPokemon(new Squirtle("Squirtle"));
    opponentOne.addPokemon(new Bulbasaur("Bulbasaur"));
    opponentOne.addPokemon(new Charmander("Charmander"));

    bool restart = true;
    while (restart) {
        arena.startBattle(&challengerOne, &opponentOne);

        std::cout << "\n\n";  // Add white spaces between battles for better readability

        arena.displayScoreboard();

        std::cout << "Do you want to restart? (y/n): ";
        std::string input;
        std::cin >> input;

        restart = (input == "y" || input == "Y");
        if (restart) {
            arena.resetScoreboard();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining newline character
    }

    return 0;
}
