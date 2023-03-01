#ifndef Door_h
#define Door_h

#include "passive.h"
#include "floor.h"
#include "wall.h"

class Door: public Floor, public Wall, public Passive
{
private:
    bool isOpen;
public:
    Door(int row, int col);
    bool isOpend();
    void notify(Active* source) override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
    string getTexture() override;
};

#endif
