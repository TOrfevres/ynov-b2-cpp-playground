//
// Created by Théodore Orfèvres on 12/02/2018.
//

#include <iostream>
#include <cmath>

#include "Monster.h"

Monster::Monster() :
        name("error"),
        strength(0), health(0), critChance(0),
        isMale(false), error(true) {
}

Monster::Monster(Utils &utils, bool isMale) :
        name(utils.getRandName(isMale)),
        strength(rand() % 25 + 25), health(rand() % 25 + 25), critChance(rand() % 5 + 1),
        isMale(isMale), error(false){
}

void Monster::desc() {
    cout << "----- MONSTER -----" << endl <<
          "Name: " << name << " (" << (isMale ? "Male" : "Female") << ")" << endl <<
          "Experience: " << exp << " (LVL " << getLevel() << ")" << endl <<
          "Energy: " << energy << " out of 3" << endl <<
          "Health: " << health << " HP" << endl <<
          "Strength: " << strength << " STR" << endl <<
          "Critic Chance: " << critChance << "%" << endl <<
          "Value: " << getValue() << "$" << endl << endl;
}

int Monster::getValue()const {
    return static_cast<int>(static_cast<float>(health * (isMale ? 0.5 : 2) + strength * (isMale ? 2 : 0.5)) / 10 * getLevel());
}

bool Monster::isCrit() {
    return rand() % 100 <= critChance;
}

const string &Monster::getName() const {
    return name;
}

int Monster::getStrength() const {
    return strength;
}

int Monster::getHealth() const {
    return health;
}

bool Monster::getIsMale() const {
    return isMale;
}

int Monster::getLevel()const {
    return static_cast<int>(floor(sqrt(Monster::exp))) + 1;
}

void Monster::addExp(int newExp) {
    int lvlBefore = getLevel();
    Monster::exp += newExp;
    for (int i = 0; i < (getLevel() - lvlBefore); i++) {
        for(int j = 0; j < 3; j++) {
            switch (rand() % 3) {
                case 0:
                    health += 3 * (isMale ? 1 : 2);
                    break;
                case 1:
                    strength += 3 * (isMale ? 2 : 1);
                    break;
                case 2:
                    critChance += 1;
                    break;

                default: break;
            }
        }
    }
}

void Monster::setStrength(int strength) {
    Monster::strength = strength;
}

void Monster::setHealth(int health) {
    Monster::health = health;
}

void Monster::tired() {
    energy--;
}

int Monster::getEnergy() const {
    return energy;
}

string Monster::getGender()const {
    return isMale ? "Male" : "Female";
}

void Monster::sleep() {
    energy = 3;
}

bool Monster::fightAgainst(Monster &monster, int currentLevel) {
    monster.addExp((int) (pow(((float) currentLevel) * (1 + ((float) currentLevel)/(rand() % 50 + 50)), 2)));

    cout << "----- FIGHT -----" << endl <<
         name << " (LVL " << getLevel() << ") VS " <<
         monster.getName() << " (LVL " << monster.getLevel() << ") !" << endl <<
         "----- ----- -----" << endl <<
         health << " HP - " << monster.getHealth() << " HP" << endl <<
         strength << " STR - " << monster.getStrength() << " STR" << endl <<
         critChance << " % - " << monster.getCritChance() << " %" << endl;

    int maxHPSelf = getHealth();
    int maxHPOpp = monster.getHealth();

    while (true) {
        // First : self -> opponent
        auto damage = strength * (isCrit() ? 2 : (float) (rand() % 5 + 5) / 10);
        if (damage > strength) cout << "CRITIC ! ";
        cout << name << " deal " << damage << " to " << monster.getName() << endl;
        maxHPOpp -= damage;

        if (maxHPOpp <= 0) {
            cout << name << " (you) WON ! (+" << min(monster.getValue() / 10, 100) << " XP)" << endl;
            addExp(min(monster.getValue() / 10, 100));
            return true;
        }

        // Second : self <- opponent
        damage = monster.getStrength() * (monster.isCrit() ? 2 : (float) (rand() % 5 + 5) / 10);
        if (damage > monster.getStrength()) cout << "CRITIC ! ";
        cout << monster.getName() << " deal " << damage << " to " << name << endl;
        maxHPSelf -= damage;

        if (maxHPSelf <= 0) {
            cout << name << " (you) LOSE ... (+" << min(monster.getValue() / 100, 100) << " XP ; -1 Energy)" << endl;
            addExp(min(monster.getValue() / 100, 225));
            return false;
        }
    }
}

int Monster::getCritChance() const {
    return critChance;
}

void Monster::isAnError() {
    Monster::error = true;
}

bool Monster::isError() {
    return error;
}

int Monster::getExp() const {
    return exp;
}

void Monster::setName(const string &name) {
    Monster::name = name;
}

void Monster::setExp(int exp) {
    Monster::exp = exp;
}

void Monster::setCritChance(int critChance) {
    Monster::critChance = critChance;
}

void Monster::setEnergy(int energy) {
    Monster::energy = energy;
}

void Monster::setIsMale(bool isMale) {
    Monster::isMale = isMale;
}

void Monster::setError(bool error) {
    Monster::error = error;
}
