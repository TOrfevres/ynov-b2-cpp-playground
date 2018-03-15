//
// Created by Théodore Orfèvres on 14/03/2018.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <boost/algorithm/string.hpp>

#include "Utils.h"

Utils::Utils(const std::string path) {
    srand((unsigned int) (time(nullptr)));

    ifstream fileOfNames(path);
    string line;
    while (getline(fileOfNames, line)) {
        names.push_back(line);
    }
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Tell if a vector has a certain int value (index)
 * @param v vector
 * @param x index (int)
 * @return hasIndex (bool)
 */
bool Utils::hasIndex(vector<int> v, int x) {
    for (int y : v) {
        if (y == x) return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Translate amount of days played into a date
 * @return readable date
 */
string Utils::getReadableCustomDate(int days) {
    return to_string(days / 360) + "Y-" +
            std::to_string((days / 30) % 12) + "M-" +
            std::to_string(days % 30) + "D";
}

//------------------------------------------------------------------------------------------------------------------O
/**
 * Get a random name from the list built with a txt file
 * @return name (char *)
 */
string Utils::getRandName(bool isMale) {
    string name;
    vector<string> values;

    do {
        name = names.at(rand() % names.size());
        boost::split(values,name,boost::is_any_of(","));
    } while (values.at(1) == (isMale ? "Boy" : "Girl"));

    return values.at(0);
}

//------------------------------------------------------------------------------------------------------------------O
vector<string> Utils::getNames() const {
    return names;
}
