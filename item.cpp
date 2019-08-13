#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include "character.h"
#include "item.h"

using namespace std;

Item::~Item(){
    cout << "deleting an Item" << endl;
}

Potion::Potion(){
    set_display('!');
    int random_type = rand()%6;
    
    if(random_type == 0){
        char arr[2] ={'R', 'H'};
        set_type(arr);
    } else if(random_type ==1){
        char arr[2] = {'B','A'};
        set_type(arr);
    }else if (random_type == 2){
        char arr[2] = {'B', 'D'};
        set_type(arr);
    }else if (random_type == 3){
        char arr[2] = {'P', 'H'};
        set_type(arr);
    }else if (random_type == 4){
        char arr[2] = {'W', 'A'};
        set_type(arr);
    }else if(random_type == 5){
        char arr[2] = {'W', 'D'};
        set_type(arr);
    }else{
        cout << "error in potion init" << endl;
    }
};

Potion::~Potion(){
    cout << "drinking potions" << endl;
}



Gold::Gold(){
    set_display('$');
    int spawn = rand()%7;
    if(spawn > 5){
        char arr[2] = {'D','H'};
        set_type(arr);
    } else{
        char arr[2] = { 'G', 'P'};
        set_type(arr);
    }
}
Gold::~Gold(){
    cout << "GOLD is being collected" << endl;
}


