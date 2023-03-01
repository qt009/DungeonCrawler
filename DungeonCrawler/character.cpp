#include <iostream>
#include "character.h"
#include "tile.h"

using std::cout;
using std::cin;

int Character::getStrength() const
{
    return strength;
}

int Character::getStamina() const
{
    return stamina;
}

int Character::getHitpoints() const
{
    return hitpoints;
}

void Character::setStrength(int newStrength)
{
    strength = newStrength;
}

void Character::setStamina(int newStamina)
{
    stamina = newStamina;
}

void Character::setHitpoints(int newHitpoints)
{
    hitpoints = newHitpoints;
}

bool Character::getIsNPC() const
{
    return isNPC;
}

bool Character::getIsAlive() const
{
    return isAlive;
}

void Character::setIsAlive(bool newIsAlive)
{
    isAlive = newIsAlive;
}

Character::Character(string texture, Controller* controller, int strength, int stamina, bool ishuman):
    Texture(texture),
    tile(nullptr),
    controller(controller),
    strength(strength),
    stamina(stamina),
    hitpoints(getMaxHP()),
    isHuman(ishuman),
    isAlive(true)
{
    isNPC = false;
}

Character::Character(string texture, Controller* controller): Texture(texture), tile(nullptr), controller(controller)
{
}

string Character::getTexture() const
{
    return Texture;
}

Tile* Character::getTile()
{
    return tile;
}

Controller* Character::getController()
{
    return controller;
}

char Character::getMoveDirection()
{
    return moveDirextion;
}

//char Character::move()
//{
////    char x;
////    cout<<"Direction: ";
////    cin>>x;
////    moveDirextion = x;
//    moveDirextion = controller->move();
//    return moveDirextion;
//}

int Character::getMaxHP()
{
    return (20 + stamina*5);
}

void Character::attack(Character *defender)
{
    defender->setHitpoints(defender->getHitpoints()-strength);
}

void Character::setTile(Tile *newTile)
{
    tile = newTile;
}

void Character::setController(Controller *con)
{
    controller = con;
}

Character::Character(std::string Texture, Controller *controller, int strength, int stamina) : Texture(Texture),
    tile(nullptr),controller(controller),
    strength(strength),
    stamina(stamina)
{
    hitpoints = getMaxHP();
    isNPC = false;
    isAlive = true;
}
