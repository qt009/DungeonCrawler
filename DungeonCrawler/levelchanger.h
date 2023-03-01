#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H
#include "active.h"
#include "tile.h"
class Level;

class LevelChanger : public Active, public Tile
{
private:
    LevelChanger* connectedTile;
    Level* CurrentLevel;
    int type;
public:
    ~LevelChanger();
    LevelChanger(int row, int col, int type);
    LevelChanger(LevelChanger *connectedTile, Level *CurrentLevel, int row, int col, const string &texture = "LevelChanger");
    LevelChanger(int row, int col, Level *CurrentLevel = nullptr, LevelChanger *connectedTile = nullptr, const string &texture = "LevelChanger");
    string getTexture() override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
    LevelChanger *getConnectedTile() const;
    void setConnectedTile(LevelChanger *newConnectedTile);
    Level *getCurrentLevel() const;
    void setCurrentLevel(Level *newCurrentLevel);
    int getType() const;
    void setType(int newType);
};

#endif // LEVELCHANGER_H
