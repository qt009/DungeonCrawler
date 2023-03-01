#include "door.h"

Door::Door(int row, int col):Tile("Door", row, col), Floor(row, col), Wall(row, col), Passive(), isOpen(false)
{
}

bool Door::isOpend()
{
    return isOpen;
}

string Door::getTexture()
{
    if (isOpen)
        return "OpenDoor";
    else
        return "CloseDoor";
}

void Door::notify(Active* source)
{
    isOpen = !isOpen;
}

Tile* Door::onEnter(Tile* fromTile, Character* who)
{
    if(isOpen){
        return Floor::onEnter(fromTile, who);
    }
    else{
        return Wall::onEnter(fromTile, who);
    }
}
