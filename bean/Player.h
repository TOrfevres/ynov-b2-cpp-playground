//
// Created by Théodore Orfèvres on 12/02/2018.
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

    Monster breeding(Utils &utils, Monster &pOne, Monster &pTwo);
    void earnGold(int x);
    bool loseGold(int x);

    const string &getName() const;
    vector<Monster> &getMonsters();
    int getGold();

    void addMonster(Monster &monster);

    void setName(const string &name);
    void setMonsters(const vector<Monster> &monsters);
    void setGold(int gold);
};


#endif //INITIATION_PLAYER_H
