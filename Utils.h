//
// Created by Théodore Orfèvres on 14/03/2018.
//

#ifndef INITIATION_UTILS_H
#define INITIATION_UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <boost/algorithm/string.hpp>
using namespace std;

class Utils {
private:
    vector<string> names;

public:
    Utils(string string);
    string getReadableCustomDate(int days);
    string getRandName(bool isMale);
    vector<string> getNames() const;
    bool hasIndex(vector<int> v, int x);
};


#endif //INITIATION_UTILS_H
