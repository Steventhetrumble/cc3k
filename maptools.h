#ifndef __character_H_INCLUDED__
#define __character_H_INCLUDED__ 

// #ifndef __item_H_INCLUDED__
// #define __item_H_INCLUDED__


class Character;
class Player;
class Orc;
class Item;
class Potion;
class Gold;

class Map
{
    int floor;
    char **map;

public:
    Map() { map = load_map(); }
    char **load_map();
    void print_map();
    bool is_tile(char floor_cell);
    bool is_stairs(char floor_cell);
    char get_cell(int location[2]) { return map[location[0]][location[1]]; }
    void set_cell(int location[2], char c) { map[location[0]][location[1]] = c; }
    void spawn_character(Character *hero);
    void spawn_stairs(int hero_room);
    bool is_passage(char floor_cell);
    std::vector<Item> spawn_items();
    std::vector<Item*> spawn_pots();
    std::vector<Item*> spawn_gold();
    Character * spawn_npcs();
    std::vector<Character*> spawn_npcs2();
    void spawn_location(int location[2]);
    
};

 // __MYCLASS_H_INCLUDED__
#endif
//#endif