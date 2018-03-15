//
// Created by Théodore Orfèvres on 15/03/2018.
//

#include "SaveIO.h"

SaveIO::SaveIO(const string &path) : path(path) {
}

void SaveIO::save(Save save) {
    ptree out;
    out.put("save.player.name", save.player.getName());

    ptree children;
    vector<Monster> inventory = save.player.getMonsters();
    for (Monster m : inventory) {
        // Each Monster
        ptree inner;
        inner.put("name", m.getName());
        inner.put("exp", m.getExp());
        inner.put("strength", m.getStrength());
        inner.put("health", m.getHealth());
        inner.put("critChance", m.getCritChance());
        inner.put("energy", m.getEnergy());
        inner.put("isMale", m.getIsMale());
        inner.put("error", m.isError());

        children.push_back(std::make_pair("", inner));
    }

    out.add_child("save.player.monsters", children);
    out.put("save.player.gold", save.player.getGold());
    out.put("save.days", save.days);

    std::ostringstream oss;
    boost::property_tree::write_json(oss, out);

    ofstream saveFile(path, ios::trunc);
    saveFile << oss.str();
    saveFile.close();
}

Save SaveIO::load() {
    ptree in;
    boost::property_tree::read_json(path, in);

    vector<Monster> monsters;
    for (ptree::value_type &m : in.get_child("save.player.monsters")) {
        Monster monster;
        monster.setName(m.second.get<string>("name"));
        monster.setStrength(m.second.get<int>("strength"));
        monster.setHealth(m.second.get<int>("health"));
        monster.setCritChance(m.second.get<int>("critChance"));
        monster.setEnergy(m.second.get<int>("energy"));
        monster.setExp(m.second.get<int>("exp"));
        monster.setIsMale(m.second.get<bool>("isMale"));
        monster.setError(m.second.get<bool>("error"));

        monsters.push_back(monster);
    }

    Player player("error");
    player.setName(in.get<string>("save.player.name"));
    player.setGold(in.get<int>("save.player.gold"));
    player.setMonsters(monsters);

    return {player, in.get<int>("save.days")};
}
