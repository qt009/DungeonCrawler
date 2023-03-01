#ifndef NPC_H
#define NPC_H
#include "character.h"
#include "stationarycontroller.h"
class NPC : public Character
{
public:
    NPC();
    NPC(const string &texture, Controller *controller = new StationaryController());
    NPC(const string &texture, int strength, int stamina, Controller *controller = new StationaryController());
    string getTexture() const override;
    char move() override;
private:
    StationaryController* staController;
};

#endif // NPC_H
