#ifndef DungeonCrawler_h
#define DungeonCrawler_h

#include <stdio.h>
#include "level.h"
#include "passive.h"
#include "abstraktui.h"
#include"list.h"

class TerminalUI;
class Controller;
class GraphicalUI;
class List;

class DungeonCrawler : public Passive
{
public:

private:
    AbstraktUI* abstraktUI;
    Level* level;
    vector<Character*> characters;
    vector<Level*> levels;
    List* list = nullptr;
    List::iterator iter;

    bool hasChangedLevel;
public:
    DungeonCrawler();
    void establishConnections();
    void play();
    void initList(Character* character);
    void setLevel(Level* levl);
    void attachWithLvlChanger();

    Level* getLevel();
    GraphicalUI* grapUI;
    const vector<Character *> &getCharacters() const;
    void notify(Active* source) override;
    bool getHasChangedLevel() const;
    void setHasChangedLevel(bool newHasChangedLevel);
};
#endif /* DungeonCrawler_hpp */
