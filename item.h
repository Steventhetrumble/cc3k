

class Character;
class Player;
class Orc;
class Dragon;

class Item
{
private:
    int *location = new int[2];
    char display;
    char *type = new char[2];
public:
    virtual ~Item();
    char * get_type() { return type; }
    void set_type(char t[2]){
        type[0] = t[0];
        type[1] = t[1];
    }
    char get_display(){ return display;}
    void set_display(char d){ display = d;}
    void set_location(int loc[2]) {
         location[0] = loc[0];
         location[1] = loc[1]; }
    int * get_location(){ return location; }
    virtual void collect_gold(Character actor){ ;}
    virtual void set_dragons_location(int * loc){ ;};
    virtual bool dragon_is_dead(){ return false;}
};

class Potion : public Item
{
public:
    Potion();
    ~Potion(); 
};

class Gold : public Item
{
private:
    Character * d = new Dragon();
    
public:
    Gold();
    ~Gold();
    bool dragon_is_dead(){ return d->is_dead();}
    void set_dragons_location(int * loc){ d->set_location(loc);}

};


