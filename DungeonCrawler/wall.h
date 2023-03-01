#ifndef Wall_h
#define Wall_h

#include "tile.h"

class Wall: virtual public Tile
{
public:
    Wall(int row, int col);
    string getTexture() override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
};

#endif /* Wall_h */
