#include <iostream>
#include <vector>
#include <string>
#include <random>


/// <summary>
/// Pokemon class 
/// </summary>
class Pokemon {
public:
    Pokemon(const std::string& name, const std::string& type)
        : name(name), type(type) {}

    const std::string& getName() const {
        return name;
    }

    const std::string& getType() const {
        return type;
    }

private:
    std::string name;
    std::string type;
};

class Battle {
public:
    static const Pokemon* fight(const Pokemon* pokemon1, const Pokemon* pokemon2) {
        if (pokemon1->getType() == "fire" && pokemon2->getType() == "grass") {
            return pokemon1;
        }
        else if (pokemon1->getType() == "grass" && pokemon2->getType() == "water") {
            return pokemon1;
        }
        else if (pokemon1->getType() == "water" && pokemon2->getType() == "fire") {
            return pokemon1;
        }
        else if (pokemon2->getType() == "fire" && pokemon1->getType() == "grass") {
            return pokemon2;
        }
        else if (pokemon2->getType() == "grass" && pokemon1->getType() == "water") {
            return pokemon2;
        }
        else if (pokemon2->getType() == "water" && pokemon1->getType() == "fire") {
            return pokemon2;
        }
        else {
            return nullptr;
        }
    }
};

class Arena {
public:
    static int rounds;
    static int battles;
};

int Arena::rounds = 0;
int Arena::battles = 0;

class Trainer {
public:
    Trainer(const std::string& name, const std::vector<Pokemon>& pokemons)
        : name(name), pokemons(pokemons) {}

    const std::string& getName() const {
        return name;
    }

    const Pokemon* get_random_pokemon() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, pokemons.size() - 1);
        return &pokemons[dis(gen)];
    }

private:
    std::string name;
    std::vector<Pokemon> pokemons;
};

class BattleArena {
public:
    static void start_battle(const Trainer& trainer1, const Trainer& trainer2) {
        Arena::battles++;
        const Pokemon* trainer1_pokemon = trainer1.get_random_pokemon();
        const Pokemon* trainer2_pokemon = trainer2.get_random_pokemon();
        const std::string& trainer1_name = trainer1.getName();
        const std::string& trainer2_name = trainer2.getName();
        const std::string& pokemon1_name = trainer1_pokemon->getName();
        const std::string& pokemon2_name = trainer2_pokemon->getName();
        const std::string& pokemon1_type = trainer1_pokemon->getType();
        const std::string& pokemon2_type = trainer2_pokemon->getType();
        const Pokemon* winner = nullptr;
        while (winner == nullptr) {
            std::cout << "Round: " << Arena::rounds + 1 << std::endl;
            std::cout << trainer1_name << "'s " << pokemon1_name << " vs. " << trainer2_name << "'s " << pokemon2_name << std::endl;
            winner = Battle::fight(trainer1_pokemon, trainer2_pokemon);
            if (winner == nullptr) {
                std::cout << "It's a draw!" << std::endl << std::endl;
                if (Arena::rounds > 0) {
                    winner = (winner == trainer1_pokemon) ? trainer2_pokemon : trainer1_pokemon;
                    std::cout << "Previous winner " << winner->getName() << " returns to their pokeball." << std::endl << std::endl;
                }
            }
            else {
                std::cout << winner->getName() << " wins the round!" << std::endl << std::endl;
            }
            Arena::rounds++;
        }

        std::cout << "Battle over!" << std::endl;
        if (winner == trainer1_pokemon) {
            std::cout << trainer1_name << " wins the battle!" << std::endl;
        }
        else {
            std::cout << trainer2_name << " wins the battle!" << std::endl;
        }
    }
};

int main() {
    std::string trainer1_name;
    std::string trainer2_name;
    std::string restart;

    Pokemon pokemon1("Charmander", "fire");
    Pokemon pokemon2("Bulbasaur", "grass");
    Pokemon pokemon3("Squirtle", "water");

    std::cout << "Enter Trainer 1's name: ";
    std::cin >> trainer1_name;
    Trainer trainer1(trainer1_name, { pokemon1, pokemon2, pokemon3 });

    std::cout << "Enter Trainer 2's name: ";
    std::cin >> trainer2_name;
    Trainer trainer2(trainer2_name, { pokemon1, pokemon2, pokemon3 });

    do {
        BattleArena::start_battle(trainer1, trainer2);

        std::cout << "Enter (R) to restart or any other key to quit: ";
        std::cin >> restart;
        Arena::rounds = 0;
        Arena::battles = 0;
    } while (restart == "R" || restart == "r");

    return 0;
}
