#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "character.h"

using namespace std;


Character::~Character(){
    cout << "Deleting a character." << endl;
}
void Character::set_Def(int def){
    if(def > 100){
        Def = 100;
    } else if(def < 0){
        Def = 0;
    } else{
        Def = def;
    }
}
void Player::print_info(){
    cout << "Class:" << player_class <<"  GP:" << gold << "  Floor:" << floor << endl;
    cout << "HP: " << get_HP() << "/" << get_max_hp() << " Atk: "<< get_Atk() + get_Def_modifier()<<"   Def: " << get_Def() + get_Def_modifier() << "%    Turn:" << turn << endl;
}

Player::~Player(){
    cout << "the Player has died." << endl;
}

Orc::~Orc(){
    cout << "the Orc has died." << endl;
}

Dragon::~Dragon(){
    cout << "the Dragon has died." << endl;
}

Grid_Bug::~Grid_Bug(){
    cout << "the Grid Bug has died." << endl;
}

Goblin::~Goblin(){
    cout << "the Goblin has died." << endl;
}

Merchant::~Merchant(){
    cout << "the Merchant has died." << endl;
}