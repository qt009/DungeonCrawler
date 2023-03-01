#ifndef Floor_h
#define Floor_h

#include "tile.h"

class Floor: virtual public Tile
{
public:
    Floor(int row, int col);
    string getTexture() override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
};

#endif /* Floor_h */
