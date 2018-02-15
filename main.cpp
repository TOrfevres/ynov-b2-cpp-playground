#include <iostream>
#include <fstream>
#include <ctime>

#include "bean/Monster.h"
#include "bean/Player.h"

int day = 1;
bool quit = false, run = true;
vector<string> names;

//------------------------------------------------------------------------------------------------------------------O
/**
 * Get a random name from the list built with a txt file
 * @return name (char *)
 */
string getRandName() {
    return names.at(rand() % names.size());
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Translate amount of days played into a date
 * @return readable date
 */
string getReadableCustomDate() {
    return to_string(day / 360) + "Y-" + to_string((day / 30) % 12) + "M-" + to_string(day % 30) + "D";
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Tell if a vector has a certain int value (index)
 * @param v vector
 * @param x index (int)
 * @return hasIndex (bool)
 */
bool hasIndex(vector<int> v, int x) {
    for (int y : v) {
        if (y == x) return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Print Monsters with an index reusable from a list
 * @param list (voector of Monster)
 * @param energy minimum energy required to be printed (int)
 * @return all indexes of printed items
 */
vector<int> printSuccinctList(vector<Monster> list, int energy) {
    vector<int> v;

    for (unsigned int i = 0; i < list.size(); i ++) {
        if (list.at(i).getEnergy() >= energy) {
            v.push_back(i);
            cout << (i + 1) << "- " << list.at(i).getValue() << "$ > " <<
                 list.at(i).getName() << " is a " <<
                 list.at(i).getGender() << " level " <<
                 list.at(i).getLevel() << " (" <<
                 list.at(i).getEnergy() << "/3)" << endl;
        }
    }

    return v;
}
//------------------------------------------------------------------------------------------------------------------O
/**
 * Menu manager of fights
 * @param player
 */
void dungeonMenu(Player &player) {
    cout << "----- DUNGEON -----" << endl <<
         "Enter the index of the monster you want to send fighting:" << endl <<
         "0- Return to main menu" << endl;

    vector<int> v = printSuccinctList(player.getMonsters(), 0);

    cout << ">";
    unsigned int monsterIndex = 0;
    cin >> monsterIndex;
    cout << endl;
    if (v.empty()) {
        cout << "You have no monster available ..." << endl;
        monsterIndex = 0;
    }
    if (monsterIndex == 0) {
        run = false;
    } else if (monsterIndex > 0 && monsterIndex <= player.getMonsters().size()) {

        Monster &trainedM = player.getMonsters().at(monsterIndex - 1);

        while (trainedM.getEnergy() > 0) {
            Monster wildM(getRandName());
            if (!trainedM.fightAgainst(wildM, trainedM.getLevel())) trainedM.tired();
        }

        run = false;
    }
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Menu manager of player inventory
 * @param player
 */
void inventoryMenu(Player &player) {
    Monster child("error");
    vector<int> v, vt;

    cout << "----- INVENTORY (WALLET: " << player.getGold() << "$) -----" << endl <<
         "Enter the index of the chosen action :" << endl <<
         "1- List your monsters" << endl <<
         "2- Breed your monsters" << endl <<
         "3- Summon a monster (100$)" << endl <<
         "4- Sell a monster" << endl <<
         "0- Return to main menu" << endl <<
         "> ";

    int action;
    cin >> action;
    cout << endl;
    switch (action) {
        case 0:
            run = false;
            break;

        case 1:
            for (Monster monster : player.getMonsters()) {
                monster.desc();
            }
            break;

        case 2:
            if (player.getMonsters().empty()) break;

            unsigned int firstMonsterIndex;
            unsigned int secondMonsterIndex;

            cout << "----- BREEDING -----" << endl <<
                 "Enter the index of the first monster you want to breed: " << endl;
            v = printSuccinctList(player.getMonsters(), 2);
            if (v.size() <= 1) {
                cout << "Not enough monster available to breed ..." << endl;
                break;
            }
            while (true) {
                cout << ">";
                cin >> firstMonsterIndex;
                cout << endl;
                if (firstMonsterIndex > 0 && firstMonsterIndex <= player.getMonsters().size() &&
                        hasIndex(v, firstMonsterIndex)) break;
            }

            cout << "Enter the index of the second monster you want to breed: " << endl;
            v = printSuccinctList(player.getMonsters(), 2);
            while (true) {
                cout << ">";
                cin >> secondMonsterIndex;
                cout << endl;
                if (secondMonsterIndex > 0 && secondMonsterIndex <= player.getMonsters().size() &&
                        secondMonsterIndex != firstMonsterIndex) break;
            }

            child = player.breeding(getRandName(),
                                    player.getMonsters().at(firstMonsterIndex - 1),
                                    player.getMonsters().at(secondMonsterIndex - 1));

            if (child.getName() != "error") player.addMonster(child);

            break;

        case 3:
            if (player.loseGold(100)) {
                Monster monster(getRandName());
                player.addMonster((Monster &) monster);
                cout << endl << "You just summon " << monster.getName() << " !" << endl;
                monster.desc();
            }
            break;

        case 4:
            cout << "Enter the index of the monster you want to sell : " << endl <<
                 "0- Return to inventory menu" << endl;
            vt = printSuccinctList(player.getMonsters(), 0);
            while (true) {
                cout << ">";
                unsigned int monsterIndex;
                cin >> monsterIndex;
                cout << endl;
                if (monsterIndex == 0) {
                    break;
                } else if (monsterIndex > 0 && monsterIndex <= player.getMonsters().size()) {

                    cout << endl << player.getMonsters().at(monsterIndex - 1).getName() << " sold ! You earn " <<
                         player.getMonsters().at(monsterIndex - 1).getValue() << "$ !" << endl << endl;
                    player.earnGold(player.getMonsters().at(monsterIndex - 1).getValue());
                    player.getMonsters().erase(player.getMonsters().begin() + (monsterIndex-1));
                    break;
                }
            }
            break;

        default:break;
    }
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Main menu
 * @param player
 */
void mainMenu(Player &player) {
    cout << "----- WELCOME " << player.getName() << " ! -----" << endl <<
         "In game date : " << getReadableCustomDate() << endl <<
         "Enter the index of the chosen action :" << endl <<
         "1- Manage your inventory" << endl <<
         "2- Go to dungeon" << endl <<
         "3- Sleep until the next day" << endl <<
         "0- Quit game" << endl <<
         "> ";

    int action;
    cin >> action;
    cout << endl;
    switch (action) {
        case 0:
            quit = true;
            break;

        case 1:
            while (run) {
                inventoryMenu(player);
            }
            run = true;
            break;

        case 2:
            while (run) {
                dungeonMenu(player);
            }
            run = true;
            break;

        case 3:
            day++;
            for (Monster &monster : player.getMonsters()) {
                monster.sleep();
            }
            break;

        default:break;
    }
}

//------------------------------------------------------------------------------------------------------------------O
int main() {
    srand((unsigned int) (time(nullptr)));

    ifstream fileOfNames("..\\names.txt");
    string line;
    while (getline(fileOfNames, line)) {
        names.push_back(line);
    }

    cout << "Size of the list of names: " << names.size() << " (x!=0 OR SHUTDOWN)" << endl
         << "Enter your name: ";
    string name;
    cin >> name;
    cout << endl;
    Player player(name);

    player.addMonster(*new Monster(getRandName()));

    while (true) {
        mainMenu((Player &) player);
        if (quit) break;
    }

    return 0;
}