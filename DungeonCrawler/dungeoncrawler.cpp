#include "dungeoncrawler.h"
#include "terminalui.h"
#include "controller.h"
#include "stationarycontroller.h"
#include "guardcontroller.h"
#include "graphicalui.h"
#include "levelchanger.h"
#include "player.h"
#include "npc.h"
#include "npcguard.h"
#include <random>
#include <iostream>
#include <QDebug>

using namespace std;

const vector<Character *> &DungeonCrawler::getCharacters() const
{
    return characters;
}

void DungeonCrawler::notify(Active *source)
{
    LevelChanger* lvl = static_cast<LevelChanger*>(source);
    auto oldLvl = *iter;
    if(lvl->getType()==1){
        --iter;
    }
    else{
        ++iter;
    }
    auto oldCharList = oldLvl->getCharacterlist();
    for(auto& character : oldCharList){
        if(dynamic_cast<GraphicalUI*>(character->getController()) == dynamic_cast<GraphicalUI*>(abstraktUI)){
            auto newLvl = *iter;
            newLvl->checkCharacterinList(character);
            oldCharList.erase(std::remove(oldCharList.begin(), oldCharList.end(), character), oldCharList.end());
        }
    }
    hasChangedLevel = true;
}

bool DungeonCrawler::getHasChangedLevel() const
{
    return hasChangedLevel;
}

void DungeonCrawler::setHasChangedLevel(bool newHasChangedLevel)
{
    hasChangedLevel = newHasChangedLevel;
}

DungeonCrawler::DungeonCrawler(): Passive(), abstraktUI(nullptr), level(nullptr), iter(NULL)
{
    list = new List();
    characters.resize(1);
    //establishConnections();
    //iter = list->begin();
    hasChangedLevel = false;
}

void DungeonCrawler::establishConnections()
{
    List::iterator it1 = list->begin();
    //List::iterator it2 = it1.next(1);
    while(it1.getNextLevel() != nullptr){
        auto lvc1 = (*it1)->getLevelChanger2();
        auto lvc2 = (it1.getNextLevel())->getLevelChanger1();
        if(lvc1&&lvc2){
            lvc1->setCurrentLevel(*it1);
            lvc1->setConnectedTile(lvc2);
            lvc2->setCurrentLevel(it1.getNextLevel());
            lvc2->setConnectedTile(lvc1);
            lvc1->attach(this);
            lvc2->attach(this);
        }
        ++it1;
    }
}

void DungeonCrawler::play()
{
    Character *character = new Player(grapUI, 100,100);
    characters[0] = character;
    initList(character);
    establishConnections();
    iter = list->begin();
    level = *iter;
    //level->getCharacterlist().push_back(character);
    QString path = "/home/stud/project-dungeon-crawler/DungeonCrawler";
    grapUI = new GraphicalUI(path,this);
    character->setController(grapUI);
    //TerminalUI* tui = new TerminalUI();
    //Character* character = new Character("Player", tui, 100, 100);
    abstraktUI = grapUI;
    //abstraktUI = new TerminalUI();

    while (true){
        if (hasChangedLevel){
            level =*iter;
        }
        if(grapUI->checkIfGameEnd(level)){
            return;
        }
        abstraktUI->draw(level);
        auto characterList = level->getCharacterlist();

        for(size_t i=0; i<characterList.size(); i++){
            Tile* currTile = characterList[i]->getTile();
            int charRow = currTile->getRow();
            int charCol = currTile->getCol();
            int charMove = level->getCharacterlist()[i]->move();
            switch (charMove)
            {
            case 'q': charRow--; charCol--; break;
            case 'w': charRow--;            break;
            case 'e': charRow--; charCol++; break;
            case 'a':            charCol--; break;
            case 's':                       break;
            case 'd':            charCol++; break;
            case 'z': charRow++; charCol--; break;
            case 'x': charRow++;            break;
            case 'c': charRow++; charCol++; break;
            default: cout << "ungultiger Move" << endl; break; //qDebug() << "ungültiger Move!";
            }
            if(!level->moveCharacter(currTile,level->getTile(charRow, charCol), characterList[i])){
                cout<<"Blocked"<<endl;
            }
        }
    }
}

void DungeonCrawler::initList(Character *character)
{
    int AnzahlLevel = 3;
    for (int i=0; i<AnzahlLevel; i++){
        if (i==0){
            Level* tmp = new Level(3,6);
//            for(int j=1; j<7;j++){
//                tmp->placeWall(2,j);
//            }
            tmp->placePortal(1,6);
            tmp->placePortal(3,1);
            tmp->placeLevelChanger(3,6,2);
            tmp->placeCharacter(character,1,1);
            tmp->portalLink();
            list->push_back(tmp);
            //NPC* npc = new NPC("NPC",50,50);
            //tmp->placeCharacter(npc,1,3);
        }
        else if(i==1){
            Level* tmp = new Level(6,6);
            for(int j=3; j<7;j++){
                tmp->placeWall(5,j);
            }
            NPC* npc1 = new NPC("NPC",50,50);
            tmp->placeCharacter(npc1,2,2);
            tmp->placePortal(1,6);
            tmp->placePortal(1,1);
            tmp->placeLevelChanger(2,1,2);
            tmp->placeLevelChanger(6,1,1);
            tmp->placePit(1,4);
            for(int j=3; j<6;j++){
                tmp->placePit(j,1);
                tmp->placePit(j,2);
            }
            for(int j=4; j<7;j++){
                tmp->placePit(2,j);
                tmp->placePit(3,j);
            }
            tmp->placeRamp(1,5);
            tmp->placeRamp(4,5);
            for(int j=1; j<6;j++){
                tmp->placeWall(j,3);
            }
            tmp->placeDoor(5,4);
            tmp->placeSwitch(6,6);
            tmp->portalLink();
            tmp->connectDoor();
            list->push_back(tmp);
        }
        else if(i==2){
            Level* tmp = new Level(10,10);
            NPC* npc1 = new NPC("NPC",50,50);
            NPCGuard* npc2 = new NPCGuard("NPCGuard",50,50, new GuardController("wwxx"));
            tmp->placeCharacter(npc1,7,8);
            tmp->placeCharacter(npc2,8,6);
            tmp->placeLevelChanger(1,1,1);
            tmp->placeChest(9,10);
            list->push_back(tmp);
        }
}
}

void DungeonCrawler::setLevel(Level *levl)
{
    level =levl;
}

void DungeonCrawler::attachWithLvlChanger()
{
    for(int i=1; i <= level->getHohe(); i++){
        for (int j=1; j <= level->getBreite(); j++){
            if(typeid(*level->getTile(i,j)) == typeid(LevelChanger)){
                auto x =dynamic_cast<LevelChanger*>(level->getTile(i,j));
                x->attach(this);
            }
        }
    }
}

Level *DungeonCrawler::getLevel()
{
    return level;
}

