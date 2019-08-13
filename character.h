// #ifndef __item_H_INCLUDED__
// #define __item_H_INCLUDED__
// #endif 

class Item;
class gold;
class Potion;
class Character
{
private:
    int HP, Atk, Def, room, *location = new int[2],Atk_modifier = 0, Def_modifier = 0, max_hp;
    bool hostile = false;
    char display, *buffs, drop;

public:
    virtual ~Character();
    virtual int attack() { return Atk; }
    void receive_attack(int attack_value)
    {
        int defense = 0;
        if(get_Def() + get_Def_modifier() > 100){
            defense = 100;
        }else{
            defense = get_Def()+ get_Def_modifier();
        }
        double modifier = 1 - (double)defense/100;
        double damage = attack_value * modifier;
        std::cout << defense << std::endl;
        HP -= (int)damage;
        if (HP < 0)
        {
            HP = 0;
        }
    }
    int get_HP() { return HP; }
    void turn_hostile() { hostile = true; }
    bool is_hostile() { return hostile; }
    bool is_dead() { 
        if(HP == 0){
            return true;
        } else{
            return false;
        }
    }
    char get_display() { return display; }
    void set_display(char c) { display = c; }
    void set_hp(int h) { HP = h; }
    void set_Atk(int atk) { Atk = atk; }
    void set_Def(int def);
    void set_location(int loc[]) {
         location[0] = loc[0];
         location[1] = loc[1]; }
    int * get_location(){ return location; }
    void set_room(char r) { room = (int)r; }
    int get_room() { return room; }
    int get_Atk() { return Atk; }
    int get_Def() { return Def; }
    int get_Atk_modifier(){ return Atk_modifier;}
    void set_Atk_modifier(int buff){ Atk_modifier = buff;}
    int get_Def_modifier(){ return Def_modifier;}
    void set_Def_modifier(int buff){ Def_modifier = buff;}
    void reset_buffs(){ Atk_modifier = 0, Def_modifier = 0;}
    void set_max_hp(int hp){ max_hp = hp;}
    int get_max_hp(){ return max_hp;}
    virtual void iterate_turn(){};
    virtual char get_player_class(){ return 'a';}
    virtual int get_gold(){return 0;}
    virtual void set_gold(int g){;}
    virtual void print_info(){;}
    virtual char get_drop(){return 'a';}
    virtual void iterate_floor(){;}
    virtual int get_floor(){return 0;}
};

class Player : public Character
{
private:
    int gold, floor, turn;
    char player_class;

public:
    Player(char type)
    {
        set_display('@');
        reset_buffs();
        player_class = type;
        if (player_class == 'k')
        {
            set_hp(100);
            set_max_hp(100);
            set_Atk(50);
            set_Def(50);
            gold = 0;
            floor = 1;
            turn = 1;
        }
        if (player_class == 'w')
        {
            set_hp(100);
            set_max_hp(100);
            set_Atk(50);
            set_Def(50);
            gold = 0;
            floor = 1;
            turn = 1;
        }
        if (player_class == 's')
        {
            set_hp(100);
            set_max_hp(100);
            set_Atk(50);
            set_Def(50);
            gold = 0;
            floor = 1;
            turn = 1;
        }
    }
    ~Player();
    char get_player_class() { return player_class; }
    int get_gold() { return gold; }
    void set_gold(int g) { gold = g; }
    void print_info();
    void iterate_turn(){ turn++;};
    void iterate_floor(){ floor++;}
    int get_floor(){ return floor;}
};

class Orc : public Character
{
    char drop = '$';

public:
    Orc()
    {
        set_display('O');
        set_hp(120);
        set_max_hp(120);
        set_Atk(75);
        set_Def(30);
    }
    ~Orc();
    char get_drop() { return drop; }
};

class Dragon : public Character
{
private:
    char drop = '.';

public:
    Dragon()
    {
        set_display('D');
        set_hp(150);
        set_Atk(50);
        set_Def(10);
    }
    ~Dragon(); 
    char get_drop() { return drop; }
    
};

class Grid_Bug : public Character
{
private:
    char drop = '!';

public:
    Grid_Bug()
    {
        set_display('X');
        set_hp(50);
        set_max_hp(50);
        set_Atk(20);
        set_Def(10);
    }
    ~Grid_Bug(); 
    char get_drop() { return drop; }
};

class Goblin : public Character
{
private:
    char drop = '$';

public:
    Goblin()
    {
        set_display('g');
        set_hp(75);
        set_max_hp(75);
        set_Atk(30);
        set_Def(20);
    }
    ~Goblin(); 
    char get_drop() { return drop; }
};

class Merchant : public Character
{
private:
    char drop = '$';

public:
    Merchant()
    {
        set_display('M');
        set_hp(100);
        set_max_hp(100);
        set_Atk(75);
        set_Def(5);
    }
    ~Merchant(); 
};
