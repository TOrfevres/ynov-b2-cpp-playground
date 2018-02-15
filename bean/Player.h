//
// Created by major on 12/02/2018.
//

#ifndef INITIATION_PLAYER_H
#define INITIATION_PLAYER_H

#include <stdio.h>
#include <string>
#include <vector>
#include "Monster.h"
using namespace std;

class Player {
private:
    string name;
    vector<Monster> monsters;
    int gold = 100;

public:
    Player(const string &name);

    Monster breeding(string childName, Monster &pOne, Monster &pTwo);
    void earnGold(int x);
    bool loseGold(int x);

    const string &getName() const;
    vector<Monster> &getMonsters();
    int getGold();

    void addMonster(Monster &monster);
};


#endif //INITIATION_PLAYER_H
