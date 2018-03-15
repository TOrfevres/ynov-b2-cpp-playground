#include <iostream>
#include <boost/algorithm/string.hpp>
#include <dirent.h>

#include "bean/Monster.h"
#include "bean/Player.h"
#include "SaveIO.h"

int days = 1;
bool quit = false, run = true;
Utils* utils = new Utils("..\\names.csv");

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
            Monster wildM(*utils, rand() % 2 == 0);
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
    Monster child(*utils, rand() % 2 == 0);
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
                        utils->hasIndex(v, firstMonsterIndex)) break;
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

            child = player.breeding(*utils,
                                    player.getMonsters().at(firstMonsterIndex - 1),
                                    player.getMonsters().at(secondMonsterIndex - 1));

            if (!child.isError()) player.addMonster(child);

            break;

        case 3:
            if (player.loseGold(100)) {
                Monster monster(*utils, rand() % 2 == 0);
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
         "In game date : " << utils->getReadableCustomDate(days) << endl <<
         "Enter the index of the chosen action :" << endl <<
         "1- Manage your inventory" << endl <<
         "2- Go to dungeon" << endl <<
         "3- Sleep until the next day" << endl <<
         "4- Save this game" << endl <<
         "5- Load a game" << endl <<
         "0- Quit game" << endl <<
         "> ";

    int action;
    cin >> action;
    cout << endl;

    string nameFile;
    SaveIO* svr = nullptr;

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
            days++;
            for (Monster &monster : player.getMonsters()) {
                monster.sleep();
            }
            break;

        case 4:
            cout << "Name your save: ";
            cin >> nameFile;

            char newPath[225];
            sprintf(newPath, "..\\saves\\%s.json", nameFile.c_str());

            svr = new SaveIO(newPath);
            svr->save({player, days});

            cout << "Save created !" << endl;
            break;

        case 5:
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir ("..\\saves\\")) != nullptr) {
                int i = 0;
                while ((ent = readdir (dir)) != nullptr) {
                    string dirName = ent->d_name;
                    if (dirName != "." && dirName != "..") {
                        i++;
                        printf("%d- %s\n", i, dirName.substr(0, dirName.size()-5).c_str());
                    }
                }
                closedir (dir);
            }

            cout << "Chose your save (name expected): ";
            cin >> nameFile;

            char oldPath[225];
            sprintf(oldPath, "..\\saves\\%s.json", nameFile.c_str());

            svr = new SaveIO(oldPath);
            days = svr->load().days;
            player = svr->load().player;

            cout << "Save loaded !" << endl;
            break;

        default:break;
    }
}

//------------------------------------------------------------------------------------------------------------------O
int main() {
    srand((unsigned int) (time(nullptr)));

    cout << "Enter your name: ";
    string name;
    cin >> name;
    cout << endl;
    Player player(name);

    player.addMonster(*new Monster(*utils, rand() % 2 == 0));

    while (true) {
        mainMenu((Player &) player);
        if (quit) break;
    }

    return 0;
}