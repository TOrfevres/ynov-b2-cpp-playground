//
// Created by Théodore Orfèvres on 15/03/2018.
//

#ifndef INITIATION_SAVEREADER_H
#define INITIATION_SAVEREADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "bean/Player.h"

using boost::property_tree::ptree;
using namespace std;

struct Save {
    Player player;
    int days = 0;
};

class SaveIO {
private:
    string path;

public:
    SaveIO(const string &path);
    void save(Save save);
    Save load();
};


#endif //INITIATION_SAVEREADER_H
