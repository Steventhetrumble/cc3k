#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include "maptools.h"
#include "character.h"
#include "item.h"

using namespace std;

char** Map::load_map(){
    string line;
    ifstream inFile;
    inFile.open(".//floors//1stfloor.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    char ** board = new char*[25];
    for (int i = 0; i < 25; i++){
        board[i] = new char[79];
        getline( inFile, line);
        for (int j = 0; j < 79; j++){
            board[i][j] = line[j];
        }
    }

    inFile.close();
    return board;
    
}

void Map::print_map(){
    for(int i = 0; i < 25 ; i++){
        for(int j = 0; j < 79; j++){
            if(is_tile(map[i][j])){
                cout << '.';
            }else{
                cout << map[i][j];
            }
        }
        cout << endl;
    }
}

bool Map::is_tile(char floor_cell){
    if(floor_cell == '1' || floor_cell == '2' || floor_cell == '3' || floor_cell == '4' || floor_cell == '5'){
        return true;
    } else { return false;}
}

bool Map::is_passage(char floor_cell){
    if(floor_cell == '+' || floor_cell == '#'){
        return true;
    } else { return false;}
}

bool Map::is_stairs(char floor_cell){
    if(floor_cell == '>'){
        return true;
    }else {
        return false;
    }
}

void Map::spawn_character(Character  * actor){
    char current_cell;
    bool spawned = false;
    while(!spawned){
        int location[] = {rand()%25,rand()%79};
        current_cell = get_cell(location);
        if(is_tile(current_cell)){
            actor->set_location(location);
            actor->set_room(current_cell);
            set_cell(location, actor->get_display());
            spawned = true;
        }
    }
}

void Map::spawn_stairs(int room_number){
    char current_cell;
    bool spawned = false;
    while(!spawned){
        int location[] = {rand()%25,rand()%79};
        current_cell = get_cell(location);
        if(is_tile(current_cell) && room_number != (int)current_cell){
            set_cell(location, '>');
            spawned = true;
        }
    }
}


void Map::spawn_location(int location[2]){
    char current_cell;
    bool spawned = false;
    location[0] = rand()%25;
    location[1] = rand()%79;
    while(!spawned){
        
        current_cell = get_cell(location);
        if(is_tile(current_cell)){
            spawned =true;
            
        }else{
            location[0] = rand()%25;
            location[1] = rand()%79;
        }
    }
}

vector<Item*> Map::spawn_pots(){
    vector<Item*> pots(10);
    for(int i = 0 ; i < 10; i++){
        pots[i] = new Potion();
        int * spawn_loc = new int[2];
        spawn_location(spawn_loc);
        pots[i]->set_location(spawn_loc);
        set_cell(spawn_loc,pots[i]->get_display());
    }
    return pots;
}

vector<Item*> Map::spawn_gold(){
    vector<Item*> gold(10);
    for(int i = 0; i < 10; i++){
        int * spawn_loc = new int[2];
        spawn_location(spawn_loc);
        gold[i] = new Gold();
        if(gold[i]->get_type()[0] == 'D'){
            cout << "uh oh" << endl;
            char current_cell;
            bool spawned = false;
            while(!spawned){
                for(int x = 0; x < 3; x++ ){
                    for(int y = 0; y < 3; y++){
                        int temp_array[2] = {spawn_loc[0] - 1 + x,spawn_loc[1] - 1 + y};
                        current_cell = get_cell(temp_array);
                        if( is_tile(current_cell) && !(temp_array[0] == spawn_loc[0] && temp_array[1]==spawn_loc[1]) && !spawned){
                            gold[i]->set_location(spawn_loc);
                            set_cell(spawn_loc, gold[i]->get_display());
                            gold[i]->set_dragons_location(temp_array);
                            set_cell(temp_array, 'D');
                            spawned = true;
                        }
                    }
                }
            }
        } else{
            gold[i]->set_location(spawn_loc);
            set_cell(spawn_loc, gold[i]->get_display());
        }
    }
    return gold;
}



Character * Map::spawn_npcs(){
    Character * npcs[20];
    char npc_choices[] = {'X','X','g','g','O','M'};
    for(int i =0; i < 20; i++){
        int choice = rand()%6;
        int * spawn_loc = new int[2];
        spawn_location(spawn_loc);
        char npc_type = npc_choices[choice];
        Character * temp;
        if(npc_type == 'X'){temp = new Grid_Bug();}
        else if(npc_type == 'g'){temp = new Goblin();}
        else if(npc_type == 'O'){temp = new Orc();}
        else{ temp = new Merchant();}
        temp->set_location(spawn_loc);
        set_cell(spawn_loc, temp->get_display());
        npcs[i] = temp;
    }
    return * npcs;
}
vector<Character*> Map::spawn_npcs2(){
    vector<Character*> npcs;
    char npc_choices[] = {'X','X','g','g','O','M'};
    for(int i =0; i < 20; i++){
        int choice = rand()%6;
        int * spawn_loc = new int[2];
        spawn_location(spawn_loc);
        char npc_type = npc_choices[choice];
        Character * temp;
        if(npc_type == 'X'){temp = new Grid_Bug();}
        else if(npc_type == 'g'){temp = new Goblin();}
        else if(npc_type == 'O'){temp = new Orc();}
        else{ temp = new Merchant();}
        temp->set_location(spawn_loc);
        set_cell(spawn_loc, temp->get_display());
        npcs.push_back(temp);
    }
    return npcs;
}