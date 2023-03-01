#include "level.h"
#include "floor.h"
#include "wall.h"
#include "portal.h"
#include "door.h"
#include "switch.h"
#include "pit.h"
#include "ramp.h"
#include "chest.h"
#include "player.h"
#include <random>
#include <utility>
#include "levelchanger.h"

#include <iostream>

std::random_device dev;
std::mt19937 rd(dev());

Level *Level::getNextLvl() const
{
    return nextLvl;
}

void Level::setNextLvl(Level *newNextLvl)
{
    nextLvl = newNextLvl;
}

Level *Level::getPrevLvl() const
{
    return prevLvl;
}

void Level::setPrevLvl(Level *newPrevLvl)
{
    prevLvl = newPrevLvl;
}

LevelChanger *Level::getToNext() const
{
    return toNext;
}

void Level::setToNext(LevelChanger *newToNext)
{
    toNext = newToNext;
}

LevelChanger *Level::getToPrev() const
{
    return toPrev;
}

void Level::setToPrev(LevelChanger *newToPrev)
{
    toPrev = newToPrev;
}

const vector<LevelChanger *> &Level::getLevelchangers() const
{
    return levelchangers;
}

bool Level::hasACharacter()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if(Spielfeld[i][j]->hasCharacter()) return true;;
        }
    }
    return false;
}

vector<Character *> &Level::getCharacterlist()
{
    return characterlist;
}

void Level::setCharacterlist(const vector<Character *> &newCharacterlist)
{
    characterlist = newCharacterlist;
}

Level::Level(): Hohe(10), Breite(10)
{
    Spielfeld.resize(Breite+2, vector<Tile*>(Hohe+2));

    for(int i=0; i < Hohe+2; i++){
        Spielfeld[0][i] = new Wall(0,i);
        Spielfeld[Breite+1][i] = new Wall(Breite+1,i);
    }

    for(int i=1; i <= Hohe; i++){
        for (int j=1; j <= Breite; j++){
            if((i==1) &&(j==1 or j==10)){
                Spielfeld[i][j] = new Portal(i,j);
            }
            else if(((i==4) or (i==5)) && ((j>=1) && (j<=3))){
                Spielfeld[i][j] = new Pit(i,j);
            }
            else if(((i==3) or (i == 4)) && ((j>=5) && (j<=10))){
                Spielfeld[i][j] = new Pit(i,j);
            }
            else if(((i==2) or (i==5)) && (j == 7)){
                Spielfeld[i][j] = new Ramp(i,j);
            }
            else if((i==6) && (((j>=4) && (j<=6)) or ((j >=8) && (j<=10)))){
                Spielfeld[i][j] = new Wall(i,j);
            }
            else if(((i>=1) && (i<=6))&&(j==4)){
                Spielfeld[i][j] = new Wall(i,j);
            }
            else if ((i==7) && (j ==10)) Spielfeld[i][j] = new Switch(i,j);
            else if((i==6) &&(j == 7)) Spielfeld[i][j] = new Door(i,j);
            else if((i == 9) && ((j==1) or (j==10))){
                Spielfeld[i][j] = new Portal(i,j);
            }
            else if ((i == 8) && (j == 3)) {
                Spielfeld[i][j] = new LevelChanger(i,j,this);
                auto* x =dynamic_cast<LevelChanger*>(Spielfeld[i][j]);
                levelchangers.push_back(x);
            }
            else Spielfeld[i][j] = new Floor(i,j);
        }
    }

    for(int i=0; i < Breite+2; i++){
        Spielfeld[i][0] = new Wall(i,0);
        Spielfeld[i][Hohe+1] = new Wall(i, Hohe+1);
    }
    portalLink();
    connectDoor();
}

Level::Level(int hohe, int breite): Hohe(hohe), Breite(breite)
{
    Spielfeld.resize(Hohe+2, vector<Tile*>(Breite+2));

    std::uniform_int_distribution<int> dis(1,5);

    for(int i=0; i < Breite+2; i++){
        Spielfeld[0][i] = new Wall(0,i);
        Spielfeld[Hohe+1][i] = new Wall(Hohe+1,i);
    }
    for(int i=1; i <= Hohe+1; i++){
        for (int j=1; j <= Breite+1; j++){
            Spielfeld[i][j] = new Floor(i,j);
        }
    }

    for(int i=1; i <= Hohe; i++){
        Spielfeld[i][0] = new Wall(i,0);
        Spielfeld[i][Breite+1] = new Wall(i, Breite+1);
    }
    portalLink();
}

Level::Level(int LevelType):Hohe(10), Breite(10)
{
    if(LevelType == 1){
        Level();
    }
    else{
        Spielfeld.resize(Breite+2, vector<Tile*>(Hohe+2));

        for(int i=0; i < Hohe+2; i++){
            Spielfeld[0][i] = new Wall(0,i);
            Spielfeld[Breite+1][i] = new Wall(Breite+1,i);
        }

        for(int i=1; i <= Hohe; i++){
            for (int j=1; j <= Breite; j++){
                if ((i == 7) && (j == 4)) {
                    Spielfeld[i][j] = new LevelChanger(i,j,this);
                    auto* x =dynamic_cast<LevelChanger*>(Spielfeld[i][j]);
                    levelchangers.push_back(x);
                }

                if ((i == 9) && (j == 8)) {
                    Spielfeld[i][j] = new LevelChanger(i,j,this);
                    auto* x =dynamic_cast<LevelChanger*>(Spielfeld[i][j]);
                    levelchangers.push_back(x);
                }

                else Spielfeld[i][j] = new Floor(i,j);
            }
        }

        for(int i=0; i < Breite+2; i++){
            Spielfeld[i][0] = new Wall(i,0);
            Spielfeld[i][Hohe+1] = new Wall(i, Hohe+1);
        }
        portalLink();
        connectDoor();
    }
}

Level::~Level()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            delete Spielfeld[i][j];
        }
    }
    for (int i=0; i < characterlist.size(); i++){
        delete characterlist[i];
    }
    for (int i=0; i < portallist.size(); i++){
        delete portallist[i];
    }
    for (int i=0; i < doorlist.size(); i++){
        delete doorlist[i];
    }
    for (int i=0; i < switchlist.size(); i++){
        delete switchlist[i];
    }
//    delete nextLvl;
//    delete prevLvl;
//    delete toNext;
//    delete toPrev;
}

Level::Level(const Level& l): Hohe(l.Hohe), Breite(l.Breite)
{
    Spielfeld = l.Spielfeld;
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            Tile* tile = l.getTile(i,j);
            if (typeid(*tile) == typeid(Floor)){
                auto f = dynamic_cast<Floor*>(tile);
                Spielfeld[i][j] = new Floor(*f);
            }
            if (typeid(*tile) == typeid(Wall)){
                auto w = dynamic_cast<Wall*>(tile);
                Spielfeld[i][j] = new Wall(*w);
            }
            if (typeid(*tile) == typeid(Portal)){
                auto p = dynamic_cast<Portal*>(tile);
                Spielfeld[i][j] = new Portal(*p);
            }
            if (typeid(*tile) == typeid(Door)){
                auto d = dynamic_cast<Door*>(tile);
                Spielfeld[i][j] = new Door(*d);
            }
            if (typeid(*tile) == typeid(Switch)){
                auto s = dynamic_cast<Switch*>(tile);
                Spielfeld[i][j] = new Switch(*s);
            }
            if (typeid(*tile) == typeid(Pit)){
                auto p = dynamic_cast<Pit*>(tile);
                Spielfeld[i][j] = new Pit(*p);
            }
            if (typeid(*tile) == typeid(Ramp)){
                auto r = dynamic_cast<Ramp*>(tile);
                Spielfeld[i][j] = new Ramp(*r);
            }
        }
    }
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            Tile* tile = l.getTile(i,j);
            if (typeid(*tile) == typeid(Portal)){
                auto currTile = dynamic_cast<Portal*>(tile);
                int row = currTile->getLinkPortal()->getRow();
                int col = currTile->getLinkPortal()->getCol();
                //attach destination point from copy to current field
                currTile = dynamic_cast<Portal*>(Spielfeld[i][j]);
                auto currTileDes = dynamic_cast<Portal*>(Spielfeld[row][col]);
                currTile->setLinkPortal(currTileDes);
            }
            else if(typeid(*tile) == typeid(Switch))
            {
                auto currTile = dynamic_cast<Switch*>(tile);
                for(auto o : currTile->getPassiveObjects()){
                    Door* currDoor = dynamic_cast<Door*>(o);
                    int col = currDoor->getCol();
                    int row = currDoor->getRow();

                    //umlegen vom boinder :D
                    currDoor = dynamic_cast<Door*>(Spielfeld[row][col]);
                    auto currSwitch = dynamic_cast<Switch*>(Spielfeld[i][j]);
                    currSwitch->attach(dynamic_cast<Passive*>(currDoor));
                }
            }
        }
    }
}

Level& Level::operator=(Level l)
{
    std::swap(Spielfeld, l.Spielfeld);
    return *this;
}

int Level::getHohe() const
{
    return Hohe;
}

int Level::getBreite() const
{
    return Breite;
}

Character *Level::getChar(int pos)
{
    return characterlist[pos];
}

LevelChanger *Level::getLevelChanger1()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(LevelChanger)){
                LevelChanger* s = dynamic_cast<LevelChanger*>(Spielfeld[i][j]);
                if(s->getType() == 1)
                    return s;
            }
        }
    }
    return nullptr;
}
LevelChanger *Level::getLevelChanger2()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(LevelChanger)){
                LevelChanger* s = dynamic_cast<LevelChanger*>(Spielfeld[i][j]);
                if(s->getType() == 2)
                    return s;
            }
        }
    }
    return nullptr;
}

bool Level::checkCharacterinList(Character *character)
{
    for(Character* c : characterlist){
        if(c == character){
            return false;
        }
    }
    characterlist.push_back(character);
    return true;
}

template <typename T>
void Level::eraseElement(vector<T *> &vec, int a)
{
    std::swap(vec[a], vec.back());
    vec.pop_back();
}

void Level::getAllPortal()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if (Spielfeld[i][j]->getTexture() == "Portal"){
                Portal* portal = dynamic_cast<Portal*>(Spielfeld[i][j]);
                if (portal->getLinkPortal() == nullptr){
                    portallist.push_back(portal);
                }
            }
        }
    }
}

void Level::portalLink()
{
    std::uniform_int_distribution<int> num(0,2);
    this->getAllPortal();
    while (portallist.size()>1){
        std::uniform_int_distribution<int> dis(1,portallist.size()-1);
        int randNum = dis(rd);
        int typePortalNum = num(rd);
        portallist[0]->setLinkPortal(portallist[randNum]);
        portallist[randNum]->setLinkPortal(portallist[0]);
        portallist[0]->setPortalType(typePortalNum);
        portallist[randNum]->setPortalType(typePortalNum);
        eraseElement(portallist, randNum);
        eraseElement(portallist, 0);
    }
    if (portallist.size()==1){
        int row = portallist[0]->getRow();
        int col = portallist[0]->getCol();
        delete Spielfeld[row][col];
        eraseElement(portallist, 0);
        Spielfeld[row][col] = new Floor(row, col);
    }
}

void Level::getAllDoor()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Door)){
                Door* s = dynamic_cast<Door*>(Spielfeld[i][j]);
                doorlist.push_back(s);
            }
        }
    }
}
void Level::getAllSwitch()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Switch)){
                Switch* s = dynamic_cast<Switch*>(Spielfeld[i][j]);
                switchlist.push_back(s);
            }
        }
    }
}

void Level::connectDoor()
{
    getAllDoor();
    getAllSwitch();

    while ((switchlist.size() >=1) && (switchlist.size()>=1)){
        switchlist[0]->attach(doorlist[0]);
        eraseElement(switchlist, 0);
        eraseElement(doorlist, 0);
    }
}

Tile* Level::getTile(int row, int col)
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if (Spielfeld[i][j]->isRightTile(row, col))
                return Spielfeld[i][j];
        }
    }
    return nullptr;
}

Tile* Level::getTile(int row, int col) const
{
    for(int i = 0; i < Hohe; i++){
        for (int j = 0; j < Breite; j++){
            if (Spielfeld[i][j]->isRightTile(row, col))
                return Spielfeld[i][j];
        }
    }
    return nullptr;
}

bool Level::moveCharacter(Tile *from, Tile *to, Character* character)
{
    if(character->getIsNPC()){
        return from->moveTo(to,character);
    }
    else{
        if(!to->hasCharacter()){
            return from->moveTo(to,character);
        }
        else{
            if(!to->getCharacter()->getIsNPC()){
                return from->moveTo(to, character);
            }
            else{
                return fight(character,to->getCharacter());
            }
        }
    }
}

bool Level::fight(Character *attacker, Character *defender)
{
    if (attacker!= nullptr){
        if(attacker->getIsAlive()){
            attacker->attack(defender);
            if(defender->getHitpoints()<=0){
                defender->setIsAlive(false);
                defender->getTile()->setCharacter(nullptr);
                defender->setTile(nullptr);
                characterlist.erase(characterlist.begin() + getPosinList(defender));
                delete defender;
                defender = nullptr;
            }
        }
    }
    if(defender!= nullptr){
        if(defender->getIsAlive()){
            defender->attack(attacker);
            if(attacker->getHitpoints()<=0){
                attacker->setIsAlive(false);
                attacker->getTile()->setCharacter(nullptr);
                attacker->setTile(nullptr);
                characterlist.erase(characterlist.begin() + getPosinList(attacker));
                delete attacker;
                attacker = nullptr;
            }
        }
    }
    return true;
}

void Level::placeCharacter(Character* c, int row, int col)
{
    Tile* t1 = getTile(row, col);
    if ((t1->getTexture() == "Floor")or(t1->getTexture() == "Portal") or (t1->getTexture()=="LevelChanger")){
        t1->setCharacter(c);
        c->setTile(t1);
    }
    if(!checkCharacterinList(c)){
        characterlist.push_back(c);
    }
}

void Level::randomPlayerpos(Character *character)
{
    int hohe, breite;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dis(0,fmin(Breite,Hohe-1));

    do{
        hohe = dis(mt);
        breite = dis(mt);
    }
    while((getTile(breite, hohe)->getTexture() != "Floor"));

    placeCharacter(character,breite,hohe);
}
void Level::placeWall(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Wall(row,col);
}

void Level::placePortal(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Portal(row,col);
}

void Level::placeDoor(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Door(row,col);
}

void Level::placeSwitch(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Switch(row,col);
}

void Level::placePit(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Pit(row,col);
}

void Level::placeRamp(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Ramp(row,col);
}

void Level::placeLevelChanger(int row, int col, int type)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new LevelChanger(row,col,type);
}

void Level::placeChest(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Chest(row,col);
}
bool Level::checkIfCharIsInList(Character *c)
{
    for (auto x : characterlist){
        if (x==c) return true;
    }
    return false;
}

size_t Level::getPosinList(Character *c)
{
    for (size_t i = 0; i<characterlist.size();i++){
        if(characterlist[i] == c){
            return i;
        }
    }
}

bool Level::hasPlayerWin()
{
    for(int i=0; i < Hohe+2; i++){
        for (int j=0; j < Breite+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Chest)){
                Chest* s = dynamic_cast<Chest*>(Spielfeld[i][j]);
                return s->getHasWin();
            }
        }
    }
    return false;
}

bool Level::hasPlayerLose()
{
    for(auto character : characterlist){
        if(typeid(*character) == typeid(Player)){
            if(character->getIsAlive()){
                return false;
            }
        }
    }
    return true;
}
