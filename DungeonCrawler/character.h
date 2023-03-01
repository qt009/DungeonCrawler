#ifndef Character_h
#define Character_h

#include "controller.h"
#include <string>

using std::string;

class Tile;
//class Level;
class Character
{
protected:
    string Texture;
    Tile* tile;
    Controller* controller;
    char moveDirextion;
    int strength, stamina, hitpoints;
    bool isNPC;
    bool isHuman;
    bool isAlive;
public:
    Character(string texture, Controller* controller, int strength, int stamina, bool ishuman);
    Character(string texture, Controller* controller);
    Character(string Texture, Controller *controller, int strength, int stamina);

    virtual string getTexture() const;
    Tile* getTile();
    Controller* getController();
    char getMoveDirection();
    virtual char move() = 0;
    int getMaxHP();
    void attack(Character* defender);


    void setTile(Tile* newTile);
    void setController(Controller* con);
    int getStrength() const;
    int getStamina() const;
    int getHitpoints() const;
    void setStrength(int newStrength);
    void setStamina(int newStamina);
    void setHitpoints(int newHitpoints);
    bool getIsNPC() const;
    bool getIsAlive() const;
    void setIsAlive(bool newIsAlive);
};

/*class Held: public Character
{
public:
    string getTexture() override;
};

class NPC: public Character
{
public:
    string getTexture() override;
};*/

#endif /* Character_h */
