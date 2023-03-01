#include <stdio.h>
#include "wall.h"

Wall::Wall(int row, int col): Tile("Wall", row, col)
{
}

string Wall::getTexture()
{
    return "Wall";
}

Tile* Wall::onEnter(Tile *fromTile, Character *who)
{
    return nullptr;
}
