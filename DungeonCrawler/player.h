#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player: public Character
{
public:
    Player(Controller* controller,int,int);
    ~Player()=default;
    string getTexture() const override ;
    char move() override;
};

#endif // PLAYER_H
