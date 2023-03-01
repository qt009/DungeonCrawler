#include "tile.h"

Tile::Tile(string texture, int row, int col): Texture(texture), character(nullptr), Row(row), Col(col)
{
    npc = nullptr;
}

int Tile::getRow()
{
    return Row;
}

int Tile::getCol()
{
    return Col;
}

Character *Tile::getCharacter()
{
    return character;
}

bool Tile::isRightTile(int row, int col)
{
    if ((Row == row)&&(Col == col)){
        return true;
    }
    return false;
}

bool Tile::hasCharacter()
{
    if (character == nullptr){
        return false;
    }
    return true;
}

bool Tile::hasPlayer()
{
    return player!= nullptr;
}

bool Tile::hasNPC()
{
    return npc != nullptr;
}

bool Tile::moveTo(Tile *desTile, Character* who)
{
    Tile* fromTile = this->onLeave(desTile, who);
    Tile* desTile2 = desTile->onEnter(fromTile, who);

    if((fromTile != nullptr)&&(desTile2 != nullptr)){
        if(fromTile == desTile2) return true;
        desTile2->setCharacter(who);
        fromTile->setCharacter(nullptr);
        who->setTile(desTile2);
        return true;
    }
    return false;
}
void Tile::setCharacter(Character *c){
    character = c;
}

Tile* Tile::onLeave(Tile *desTile, Character *who)
{
    return this;
}

Player *Tile::getPlayer() const
{
    return player;
}

void Tile::setPlayer(Player *newPlayer)
{
    player = newPlayer;
}

NPC *Tile::getNpc() const
{
    return npc;
}

void Tile::setNpc(NPC *newNpc)
{
    npc = newNpc;
}
