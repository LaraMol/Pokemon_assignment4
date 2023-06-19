#include <iostream>
#include <vector>
#include <string>
#include <random>


/// Pokemon class with names and types.
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


/// Battle class the rock paper scissors type of fight. type weaknesses.
class Battle {
public:
    static const Pokemon* fight(const Pokemon* pokemonOne, const Pokemon* pokemonTwo) {
        if (pokemonOne->getType() == "fire" && pokemonTwo->getType() == "grass") {
            return pokemonOne;
        }
        else if (pokemonOne->getType() == "grass" && pokemonTwo->getType() == "water") {
            return pokemonOne;
        }
        else if (pokemonOne->getType() == "water" && pokemonTwo->getType() == "fire") {
            return pokemonOne;
        }
        else if (pokemonTwo->getType() == "fire" && pokemonOne->getType() == "grass") {
            return pokemonTwo;
        }
        else if (pokemonTwo->getType() == "grass" && pokemonOne->getType() == "water") {
            return pokemonTwo;
        }
        else if (pokemonTwo->getType() == "water" && pokemonOne->getType() == "fire") {
            return pokemonTwo;
        }
        else {
            return nullptr;
        }
    }
};

/// Arena class where we save the the rounds and battles.
class Arena {
public:
    static int rounds;
    static int battles;
};

int Arena::rounds = 0;
int Arena::battles = 0;


/// Trainer class   
class Trainer {
public:
    Trainer(const std::string& name, const std::vector<Pokemon>& pokemons)
        : name(name), pokemons(pokemons) {}

    const std::string& getName() const {
        return name;
    }


    const Pokemon* get_random_pokemon() const {
        ///creates an object that is used to obtain a seed for the random number engine
        std::random_device rd;
        ///This is a random number engine that generates random numbers using the Mersenne Twister algorithm
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, pokemons.size() - 1);
        return &pokemons[dis(gen)];
    }

private:
    std::string name;
    std::vector<Pokemon> pokemons;
};
/// <summary>
/// BattleArena
/// </summary>
class BattleArena {
public:
    static void start_battle(const Trainer& Challenger, const Trainer& opponent) {
        Arena::battles++;
        const Pokemon* Challenger_pokemon = Challenger.get_random_pokemon();
        const Pokemon* opponent_pokemon = opponent.get_random_pokemon();
        const std::string& Challenger_name = Challenger.getName();
        const std::string& opponent_name = opponent.getName();
        const std::string& pokemonOne_name = Challenger_pokemon->getName();
        const std::string& pokemonTwo_name = opponent_pokemon->getName();
        const std::string& pokemonOne_type = Challenger_pokemon->getType();
        const std::string& pokemonTwo_type = opponent_pokemon->getType();
        const Pokemon* winner = nullptr;
        while (winner == nullptr) {
            std::cout << "Round: " << Arena::rounds + 1 << std::endl;
            std::cout << Challenger_name << "'s " << pokemonOne_name << " vs. " << opponent_name << "'s " << pokemonTwo_name << std::endl;
            winner = Battle::fight(Challenger_pokemon, opponent_pokemon);
            if (winner == nullptr) {
                std::cout << "It's a draw!" << std::endl << std::endl;
                if (Arena::rounds > 0) {
                    winner = (winner == Challenger_pokemon) ? opponent_pokemon : Challenger_pokemon;
                    std::cout << "Previous winner " << winner->getName() << " returns to their pokeball." << std::endl << std::endl;
                }
            }
            else {
                std::cout << winner->getName() << " wins the round!" << std::endl << std::endl;
            }
            Arena::rounds++;
        }

        std::cout << "Battle over!" << std::endl;
        if (winner == Challenger_pokemon) {
            std::cout << Challenger_name << " wins the battle!" << std::endl;
        }
        else {
            std::cout << opponent_name << " wins the battle!" << std::endl;
        }
    }
};

int main() {
    std::string Challenger_name;
    std::string opponent_name;
    std::string restart;

    Pokemon pokemonOne("Charmander", "fire");
    Pokemon pokemonTwo("Bulbasaur", "grass");
    Pokemon pokemonThree("Squirtle", "water");

    std::cout << "Enter Trainer 1's name: ";
    std::cin >> Challenger_name;
    Trainer Challenger(Challenger_name, { pokemonOne, pokemonTwo, pokemonThree });

    std::cout << "Enter Trainer 2's name: ";
    std::cin >> opponent_name;
    Trainer opponent(opponent_name, { pokemonOne, pokemonTwo, pokemonThree });

    do {
        BattleArena::start_battle(Challenger, opponent);

        std::cout << "Enter (R) to restart or any other key to quit: ";
        std::cin >> restart;
    } while (restart == "R" || restart == "r");

    return 0;
}
