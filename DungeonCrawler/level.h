#ifndef Level_h
#define Level_h

#include <stdio.h>
#include <array>
#include <vector>
#include "tile.h"
#include "character.h"

using std::array;
using std::vector;

class Controller;
class Floor;
class Wall;
class Portal;
class Door;
class Switch;
class LevelChanger;

class Level
{
private:
    vector<Character*> characterlist;
    const int Hohe;
    const int Breite;
    vector<vector<Tile*>> Spielfeld;
    vector<LevelChanger*> levelchangers;
    Controller* controller;

    vector<Portal*> portallist;
    vector<Switch*> switchlist;
    vector<Door*> doorlist;

    Level* nextLvl = nullptr;
    Level* prevLvl = nullptr;

    LevelChanger* toNext = nullptr;
    LevelChanger* toPrev = nullptr;
    bool checkIfCharIsInList(Character* c);
    size_t getPosinList(Character* c);

    bool hasPlayerWin();
    bool hasPlayerLose();


public:
    Level();
    Level(int hohe, int breite);
    Level(int LevelType);
    ~Level();
    Level(const Level& l);
    Level& operator=(Level l);
    bool hasACharacter();

    int getHohe() const;
    int getBreite() const;
    Character* getChar(int pos);
    LevelChanger *getLevelChanger1();
    LevelChanger* getLevelChanger2();
    bool checkCharacterinList(Character *character);

    template <typename T>
    void eraseElement(vector<T*>& vec, int a);

    void getAllPortal();
    void portalLink();

    void getAllDoor();
    void getAllSwitch();
    void connectDoor();

    Tile* getTile(int row, int col);
    Tile* getTile(int row, int col) const;
    bool moveCharacter(Tile* from, Tile* to, Character* character);
    bool fight(Character* attacker, Character* defender);
    void placeCharacter(Character* c, int row, int col);
    void randomPlayerpos(Character* character);

    friend class TerminalUI;
    Level *getNextLvl() const;
    void setNextLvl(Level *newNextLvl);
    Level *getPrevLvl() const;
    void setPrevLvl(Level *newPrevLvl);
    LevelChanger *getToNext() const;
    void setToNext(LevelChanger *newToNext);
    LevelChanger *getToPrev() const;
    void setToPrev(LevelChanger *newToPrev);
    const vector<LevelChanger *> &getLevelchangers() const;
    vector<Character *> &getCharacterlist();
    void setCharacterlist(const vector<Character *> &newCharacterlist);
    void placeWall(int row, int col);
    void placePortal(int row, int col);
    void placeDoor(int row, int col);
    void placeSwitch(int row, int col);
    void placePit(int row, int col);
    void placeRamp(int row, int col);
    void placeLevelChanger(int row, int col,int type);
    void placeChest(int row, int col);

    friend class MainWindow;
};

#endif
