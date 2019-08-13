#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "maptools.h"
#include "character.h"
#include "item.h"

using namespace std;

int* get_move(string s);
void spawn_items();

int main()
{
    bool game = true;
    string mode = "start";
    Map * original_map = new Map();
    Map *map;
    Character *hero;
    vector<Item*> pots;
    int number_of_pots = 10;
    vector<Item*> gold;
    int number_of_gold = 10;
    vector<Character*> npcs;
    bool players_turn;

    while(game){
        if(mode == "start"){
            string spec;
            cout << "what class would you like to play? Knight(k), Wizard(w), Samurai(s)" << endl;
            getline(cin, spec);
            if(spec[0] == 'k' || spec[0] == 'w' || spec[0] == 's'){
                cout << "you have chosen to become a knight!" << endl;
                map = new Map();
                hero = new Player(spec[0]);
                map->spawn_character(hero);
                map->spawn_stairs(hero->get_room());
                pots = map-> spawn_pots();
                gold = map->spawn_gold();
                npcs = map->spawn_npcs2();
                if(hero->get_player_class() != 's'){
                    Character * temp;
                    for(int i = 0; i < 20; i++){
                        temp = npcs[i];
                        if(temp->get_display() != 'M'){
                            temp->turn_hostile();
                        }
                    }
                }
                map->print_map();
                hero->print_info();
                mode = "playing";
                players_turn = true;
            } else {
                cout << "you must enter one of the given classes." << endl;
            }
        }else if(mode == "next_floor"){
            hero->iterate_floor();
            if(hero->get_floor() == 5){
                mode = "win";

            }else{
                hero->reset_buffs();
                map = new Map();
                map->spawn_character(hero);
                map->spawn_stairs(hero->get_room());
                pots = map-> spawn_pots();
                number_of_pots = 10;
                gold = map->spawn_gold();
                number_of_gold = 10;
                npcs = map->spawn_npcs2();
                if(hero->get_player_class() != 's'){
                    Character * temp;
                    for(int i = 0; i < 20; i++){
                        temp = npcs[i];
                        if(temp->get_display() != 'M'){
                            temp->turn_hostile();
                        }
                    }
                }
                map->print_map();
                hero->print_info();
                mode = "playing";
                players_turn = true;
            }
            
        }else if(mode == "win"){
            cout << "yay you won" << endl;
            mode = "start";

        }else if (mode == "playing"){
            if(hero->is_dead()){
                cout << "hero is dead" << endl;
                players_turn = false;
                mode = "start";
            }else if(players_turn){
                string decision;
                cout << "What will you do?" << endl;
                getline(cin, decision);
                if(decision[0] == 'r'){
                    mode = "start";
                } else if(decision[0] == 'q'){
                    mode = "end game";
                } else if(decision[0] == 'a'){
                    if( decision.size() != 4){
                        cout << "improper input" << endl;
                    } else{
                        string direction = decision.substr(2,3);
                        int * move = new int[2];
                        move = get_move(direction);
                        if(!(move[0]==0 && move[1] ==0)){
                            int target[2] = {hero->get_location()[0] + move[0], hero->get_location()[1] + move[1]};
                            for( int enemy = 0; enemy < 20; enemy++){
                                Character *temp = npcs[enemy];
                                int *enemy_location = new int[2];
                                enemy_location[0] = temp->get_location()[0];
                                enemy_location[1] = temp->get_location()[1];
                                if(enemy_location[0] == target[0]  && enemy_location[1] == target[1]){
                                    
                                    temp->receive_attack(hero->get_Atk() + hero->get_Atk_modifier());
                                    if(temp->get_display() == 'M'){
                                        for(int npc_index = 0; npc_index < 20; npc_index++){
                                            Character *merchant = npcs[npc_index];
                                            if(merchant->get_display() == 'M'){
                                                merchant->turn_hostile();
                                            }
                                        }
                                    }
                                    if(!(temp->is_hostile())){
                                        temp->turn_hostile();
                                    }
                                    if(temp->is_dead()){
                                        char drop = temp->get_drop();
                                        int arr[2] = {0,0};
                                        temp->set_location(arr);
                                        if(drop == '$'){
                                            Item * new_gold = new Gold();
                                            new_gold->set_location(enemy_location);
                                            gold.push_back(new_gold);
                                            map->set_cell(enemy_location, drop);
                                            number_of_gold++;
                                        }else if(drop == '!'){
                                            Item * new_potion = new Potion();
                                            new_potion->set_location(enemy_location);
                                            pots.push_back(new_potion);
                                            map->set_cell(enemy_location, drop);
                                            number_of_pots++;
                                        }else if(drop == '.'){
                                            char replace_cell = original_map->get_cell(temp->get_location());

                                        }else{
                                            cout << "hero attack, kills creature: error" << endl;
                                        }
                                    }
                                    players_turn = false;
                                }
                            }
                        }
                    }
                } else if(decision[0] == 'u'){
                    if( decision.size() != 4){
                        cout << "improper input" << endl;
                    } else{
                        bool found_gold = false, found_potion = false, found_horde = false;
                        string direction = decision.substr(2,3);
                        int * use = new int[2];
                        use = get_move(direction);
                        if(!(use[0]==0 && use[1] ==0)){
                            int * current_location = hero->get_location();
                            int * desired_item = new int[2];
                            desired_item[0] = current_location[0] + use[0];
                            desired_item[1] = current_location[1] + use[1];
                            for(int i =0; i < number_of_pots; i++){
                                if(pots[i]->get_location()[0] == desired_item[0] && pots[i]->get_location()[1] == desired_item[1]){
                                    cout << "you could use that potion:" <<endl;
                                    string potion_type = pots[i]->get_type();
                                    potion_type = potion_type.substr(0,2);
                                    if(potion_type == "RH"){
                                        if(hero->get_HP() + 30 > hero->get_max_hp()){
                                            hero->set_hp(hero->get_max_hp());
                                        } else{
                                            hero->set_hp(hero->get_HP() + 30);
                                        }
                                    } else if( potion_type == "BA"){
                                        hero->set_Atk_modifier(hero->get_Atk_modifier() + 10);
                                    } else if (potion_type == "BD"){
                                        hero->set_Def_modifier(hero->get_Def_modifier() + 10);

                                    } else if (potion_type == "PH"){
                                        if(hero->get_HP() - 15 < 1){
                                            hero->set_hp(0);
                                        }else{
                                            hero->set_hp(hero->get_HP() -15);
                                        }
                                    } else if(potion_type == "WA"){
                                        hero->set_Atk_modifier(hero->get_Atk_modifier() -5);
                                    } else if(potion_type == "WD"){
                                        hero->set_Def_modifier(hero->get_Def_modifier() - 5);
                                    } else{
                                        cout << "players turn: potion error" << endl;
                                    }
                                    char replace_cell = original_map->get_cell(current_location);
                                    map->set_cell(desired_item, hero->get_display());
                                    map->set_cell(current_location, replace_cell);
                                    hero->set_location(desired_item);
                                    int arr[2] = {0,0};
                                    pots[i]->set_location(arr);
                                    hero->iterate_turn();
                                    found_potion = true;
                                }
                            }
                            for(int i = 0; i < number_of_gold;i++){
                                if(gold[i]->get_location()[0] == desired_item[0] && gold[i]->get_location()[1] == desired_item[1]){
                                    string gold_type = gold[i]->get_type();
                                    gold_type = gold_type.substr(0,2);
                                    if( gold_type == "GP"){
                                        char replace_cell = original_map->get_cell(current_location);
                                        map->set_cell(desired_item, hero->get_display());
                                        map->set_cell(current_location, replace_cell);
                                        hero->set_location(desired_item);
                                        hero->set_gold(hero->get_gold() + 10);
                                        int arr[2] = {0,0};
                                        gold[i]->set_location(arr);
                                        hero->iterate_turn();
                                        found_gold = true;
                                    } else { 
                                        if(gold[i]->dragon_is_dead()){
                                            char replace_cell = original_map->get_cell(current_location);
                                            map->set_cell(desired_item, hero->get_display());
                                            map->set_cell(current_location, replace_cell);
                                            hero->set_location(desired_item);
                                            hero->set_gold(hero->get_gold() + 50);
                                            int arr[2] = {0,0};
                                            gold[i]->set_location(arr);
                                            hero->iterate_turn();
                                            found_gold = true;
                                        } else { 
                                            cout << "there is a dragon protecting this horde!" << endl;
                                            found_horde = true;
                                        }
                                    }
                                }
                            }
                            if( found_gold || found_potion){
                                players_turn = false;
                            } else{
                                if(!found_horde){
                                    cout << "there is nothing there for you to use!" << endl;
                                }
                            }
                        }
                    }
                } else{
                    if( decision.size() != 2){
                        cout << "improper input" << endl;
                    } else{
                        int * move = new int[2];
                        move = get_move(decision);
                        if(!(move[0]==0 && move[1] ==0)){
                        
                            int * current_location = hero->get_location();
                            int * desired_location = new int[2];
                            desired_location[0] = current_location[0] + move[0];
                            desired_location[1] = current_location[1] + move[1];
                            char desired_cell = map->get_cell(desired_location);
                            char replace_cell = original_map->get_cell(current_location);
                            if(map->is_stairs(desired_cell)){
                                players_turn = false;
                                mode = "next_floor";
                            }else if( map->is_tile(desired_cell) || map->is_passage(desired_cell)){
                                map->set_cell(desired_location, hero->get_display());
                                map->set_cell(current_location, replace_cell);
                                hero->set_location(desired_location);
                                hero->iterate_turn();
                                players_turn = false;
                            }else{
                                cout << "cannot move there" << endl;
                            }
                        }
                    }
                }
            }else{
                cout << "computer turn!!" << endl;
                for(int i =0; i < 20;i++){
                    Character *temp = npcs[i];
                    bool attack = false;
                    if(temp->is_dead()){
                        attack = true;
                    }
                    // TODO: need to fix the logic here
                    if(abs(hero->get_location()[0] - temp->get_location()[0]) < 2 && abs(hero->get_location()[1] - temp->get_location()[1])< 2){
                        if(temp->is_hostile()){
                            hero->receive_attack(temp->get_Atk() + temp->get_Atk_modifier());
                            attack = true;
                        }
                    }
                    
                    if(!attack){
                        string directions[8] = {"no", "so", "ea", "we","se","sw","nw","ne" };
                        if(temp->get_display() == 'X'){
                            int tries = 0;
                            bool found = false;
                            int *current_location = temp->get_location();
                            while(!found){
                                int dir = rand()%4;
                                int * move = new int[2];
                                move = get_move(directions[dir]);
                                int desired_location[2] = {current_location[0] + move[0], current_location[1] + move[1]};
                                if(map->is_tile(map->get_cell(desired_location)) || map->is_passage(map->get_cell(desired_location))){
                                    char replace_cell = original_map->get_cell(current_location);
                                    map->set_cell(desired_location, temp->get_display());
                                    map->set_cell(current_location, replace_cell);
                                    temp->set_location(desired_location);
                                    found = true;
                                }else if(tries > 20){
                                    found = true;
                                }
                                ++tries;

                            }
                            
                        } else if(temp->get_display() == 'g'){
                            int tries = 0;
                            bool found = false;
                            int *current_location = temp->get_location();
                            for( int x = 0; x < 10; x++){
                                if(abs(pots[x]->get_location()[0] - current_location[0]) < 2 && abs(pots[x]->get_location()[1] - current_location[1])< 2){
                                    string potion_type = pots[x]->get_type();
                                    potion_type = potion_type.substr(0,2);
                                    if(potion_type == "RH"){
                                        if(temp->get_HP() + 30 > temp->get_max_hp()){
                                            temp->set_hp(temp->get_max_hp());
                                        } else{
                                            temp->set_hp(temp->get_HP() + 30);
                                        }
                                    } else if( potion_type == "BA"){
                                        temp->set_Atk_modifier(hero->get_Atk_modifier() + 10);
                                    } else if (potion_type == "BD"){
                                        temp->set_Def_modifier(temp->get_Def_modifier() + 10);

                                    } else if (potion_type == "PH"){
                                        if(hero->get_HP() - 15 < 1){
                                            temp->set_hp(0);
                                        }else{
                                            temp->set_hp(temp->get_HP() -15);
                                        }
                                    } else if(potion_type == "WA"){
                                        temp->set_Atk_modifier(temp->get_Atk_modifier() -5);
                                    } else if(potion_type == "WD"){
                                        temp->set_Def_modifier(temp->get_Def_modifier() - 5);
                                    } else{
                                        cout << "players turn: potion error" << endl;
                                    }
                                    char replace_cell = original_map->get_cell(current_location);
                                    map->set_cell(pots[x]->get_location(), temp->get_display());
                                    map->set_cell(current_location, replace_cell);
                                    temp->set_location(pots[x]->get_location());
                                    int arr[2] = {0,0};
                                    pots[x]->set_location(arr);
                                    found = true;
                                }
                            }
                            while(!found){
                                int dir = rand()%4;
                                int * move = new int[2];
                                move = get_move(directions[dir]);
                                int desired_location[2] = {current_location[0] + move[0], current_location[1] + move[1]};
                                if(map->is_tile(map->get_cell(desired_location)) || map->is_passage(map->get_cell(desired_location))){
                                    char replace_cell = original_map->get_cell(current_location);
                                    map->set_cell(desired_location, temp->get_display());
                                    map->set_cell(current_location, replace_cell);
                                    temp->set_location(desired_location);
                                    found = true;
                                }else if(tries > 20){
                                    found = true;
                                }
                                ++tries;
                            }
                        } else if(temp->get_display() == 'M'){
                            int tries = 0;
                            bool found = false;
                            int *current_location = temp->get_location();
                            while(!found){
                                int dir = rand()%4;
                                int * move = new int[2];
                                move = get_move(directions[dir]);
                                int desired_location[2] = {current_location[0] + move[0], current_location[1] + move[1]};
                                if(map->is_tile(map->get_cell(desired_location)) || map->is_passage(map->get_cell(desired_location))){
                                    char replace_cell = original_map->get_cell(current_location);
                                    map->set_cell(desired_location, temp->get_display());
                                    map->set_cell(current_location, replace_cell);
                                    temp->set_location(desired_location);
                                    found = true;
                                }else if(tries > 20){
                                    found = true;
                                }
                                ++tries;
                            }
                            
                        }else if(temp->get_display() == 'O'){
                            int tries = 0;
                            bool found = false;
                            int *current_location = temp->get_location();
                            while(!found){
                                int dir = rand()%4;
                                int *move = new int[2];
                                move = get_move(directions[dir]);
                                int desired_location[2] = {current_location[0] + move[0], current_location[1] + move[1]};
                                if(map->is_tile(map->get_cell(desired_location)) || map->is_passage(map->get_cell(desired_location))){
                                    char replace_cell = original_map->get_cell(current_location);
                                    map->set_cell(desired_location, temp->get_display());
                                    map->set_cell(current_location, replace_cell);
                                    temp->set_location(desired_location);
                                    found = true;
                                }else if(tries > 20){
                                    found = true;
                                }
                                ++tries;
                            }
                        }else{
                            cout << "computer turn: get_disply() error" << endl;
                        }
                    }
                }
                players_turn = true;
                map->print_map();
                hero->print_info();

            }
        }else{
            delete hero;
            game = false;
        }

    }
    
    return 0;
}



int* get_move(string s){
    int *move = new int[2];
    if(s == "no"){
        move[0] = -1;
        move[1] = 0;
    }else if(s == "so"){
        move[0] = 1;
        move[1] = 0;
    }else if (s== "ea"){
        move[0] = 0;
        move[1] = 1;
    }else if (s == "we"){
        move[0] = 0;
        move[1] = -1;
    }else if (s == "ne"){
        move[0] = -1;
        move[1] = 1;
    }else if ( s == "nw"){
        move[0] = -1;
        move[1] = -1;
    }else if ( s == "se"){
        move[0] = 1;
        move[1] = 1;
    }else if ( s == "sw"){
        move[0] = 1;
        move[1] = -1;
    }else{
        move[0] =0;
        move[1] =0;
        cout << "improper input" << endl;
        
    }
    return move;
}
