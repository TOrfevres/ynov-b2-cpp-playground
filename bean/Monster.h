//
// Created by major on 12/02/2018.
//

#ifndef INITIATION_MONSTER_H
#define INITIATION_MONSTER_H

#include <string>
using namespace std;

class Monster {
private:
    std::string name;
    int exp = 0;
    int strength;
    int health;
    int critChance;
    int energy = 3;
    bool isMale;

    bool isCrit();

public:
    Monster(const string &name);
    Monster(const string &name, bool isMale);

    void desc();
    void sleep();
    void tired();
    bool fightAgainst(Monster &monster, int currentLevel);
    string getGender()const;

    const string &getName() const;
    int getStrength() const;
    int getHealth() const;
    bool getIsMale() const;
    int getLevel()const;
    int getValue()const;
    int getEnergy() const;

    int getCritChance() const;

    void addExp(int newExp);

    void setStrength(int strength);
    void setHealth(int health);
};


#endif //INITIATION_MONSTER_H
