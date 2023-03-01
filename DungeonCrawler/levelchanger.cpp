#include "levelchanger.h"
#include "level.h"


LevelChanger *LevelChanger::getConnectedTile() const
{
    return connectedTile;
}

void LevelChanger::setConnectedTile(LevelChanger *newConnectedTile)
{
    connectedTile = newConnectedTile;
}

Level *LevelChanger::getCurrentLevel() const
{
    return CurrentLevel;
}

void LevelChanger::setCurrentLevel(Level *newCurrentLevel)
{
    CurrentLevel = newCurrentLevel;
}

int LevelChanger::getType() const
{
    return type;
}

void LevelChanger::setType(int newType)
{
    type = newType;
}

LevelChanger::~LevelChanger()
{
    delete connectedTile;
    delete CurrentLevel;
}

LevelChanger::LevelChanger(LevelChanger *connectedTile, Level *CurrentLevel, int row, int col, const string &texture) : Tile(texture, row, col),
    connectedTile(connectedTile),
    CurrentLevel(CurrentLevel)
{}

LevelChanger::LevelChanger(int row, int col, Level *CurrentLevel, LevelChanger *connectedTile, const string &texture) : Tile(texture, row, col),
    connectedTile(connectedTile),
    CurrentLevel(CurrentLevel)
{}

string LevelChanger::getTexture()
{
    return "LevelChanger";
}

Tile *LevelChanger::onEnter(Tile *fromTile, Character *who)
{
    this->activate();
    return this->connectedTile;
}

LevelChanger::LevelChanger(int row, int col, int type) : Tile("LevelChanger", row, col), Active(),
    type(type)
{

}
