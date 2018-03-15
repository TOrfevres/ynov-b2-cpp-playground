//
// Created by Théodore Orfèvres on 12/02/2018.
//

#include <iostream>
#include "Player.h"

Player::Player(const string &name) : name(name) {}

Monster Player::breeding(Utils &utils, Monster &pOne, Monster &pTwo) {
    if (&pOne == &pTwo) {
        cout << "A monster can't breed with itself !" << endl;

        Monster error;
        return error;
    }

    int lvlDiff = abs(pOne.getLevel() - pTwo.getLevel()) / (pTwo.getLevel() + 1);
    pOne.tired(); pOne.tired();
    pTwo.tired(); pTwo.tired();

    if (pOne.getIsMale() ^ pTwo.getIsMale()) {
        int ratio = rand() % 10 + 5;

        Monster child(utils, rand() % 2 == 0);

        cout << "----- BREEDING -----" << endl <<
             pOne.getName() << " (" << (ratio * 5) << "%) and " <<
             pTwo.getName() << " (" << (100 - ratio * 5) << "%) gave birth to " <<
             child.getName() << endl;

        child.setHealth((pOne.getHealth() * ratio / 10 + pTwo.getHealth() * (20 - ratio) / 10) / 2 + rand() % 10);
        child.setStrength((pOne.getStrength() * ratio / 10 + pTwo.getStrength() * (20 - ratio) / 10) / 2 + rand() % 10);
        child.setStrength((pOne.getStrength() * ratio / 10 + pTwo.getStrength() * (20 - ratio) / 10) / 2 + rand() % 10);

        pOne.addExp(3 + pTwo.getLevel() * (lvlDiff < 2 ? lvlDiff : 2 ));
        pTwo.addExp(3 + pOne.getLevel() * (lvlDiff < 2 ? lvlDiff : 2 ));

        child.desc();

        return child;
    }

    pOne.addExp(2 + pTwo.getLevel() * (lvlDiff < 2 ? lvlDiff : 2 ));
    pTwo.addExp(2 + pOne.getLevel() * (lvlDiff < 2 ? lvlDiff : 2 ));

    Monster error;
    return error;
}

const string &Player::getName() const {
    return name;
}

vector<Monster> &Player::getMonsters() {
    return monsters;
}

void Player::addMonster(Monster &monster) {
    monsters.push_back(monster);
}

int Player::getGold() {
    return gold;
}

void Player::earnGold(int x) {
    gold += x;
}

bool Player::loseGold(int x) {
    if (x <= gold) {
        gold -= x;
        return true;
    }

    cout << "Not enough gold !" << endl;
    return false;
}

void Player::setName(const string &name) {
    Player::name = name;
}

void Player::setMonsters(const vector<Monster> &monsters) {
    Player::monsters = monsters;
}

void Player::setGold(int gold) {
    Player::gold = gold;
}
