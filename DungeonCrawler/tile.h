#ifndef Tile_h
#define Tile_h

#include <stdio.h>
#include <string>
#include "character.h"
#include "player.h"
#include "npc.h"
#include <typeinfo>

using std::string;

class Tile
{
public:
    Tile(string texture, int row, int col);
    virtual ~Tile() = default;
    virtual string getTexture() = 0;
    int getRow();
    int getCol();
    Character* getCharacter();

    bool isRightTile(int row, int col);
    bool hasCharacter();
    bool hasPlayer();

    bool hasNPC();
    void setCharacter(Character* c);

    bool moveTo(Tile* desTile, Character* who);
    virtual Tile* onEnter(Tile* fromTile, Character* who) = 0;
    virtual Tile* onLeave(Tile* desTile, Character* who);
    Player *getPlayer() const;
    void setPlayer(Player *newPlayer);

    NPC *getNpc() const;
    void setNpc(NPC *newNpc);

protected:
    string Texture;
    Character* character;
    NPC* npc;
    Player* player;
    const int Row;
    const int Col;
};


#endif /* Tile_h */
