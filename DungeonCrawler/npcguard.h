#ifndef NPCGUARD_H
#define NPCGUARD_H
#include "character.h"
#include "guardcontroller.h"

class NPCGuard : public Character
{
public:
    NPCGuard(const string &texture, int strength, int stamina, Controller *controller = new GuardController("aadd"));
    NPCGuard(int, int, string musterMove);
    char move() override;
    string getTexture() const override;
private:
    GuardController* grdcontroller;
};

#endif // NPCGUARD_H
