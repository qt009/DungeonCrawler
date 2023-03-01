#include "npcguard.h"
NPCGuard::NPCGuard(const std::string &texture, int strength, int stamina, Controller *controller)
    :Character(texture,controller, strength, stamina)
{
    isNPC = true;
}
NPCGuard::NPCGuard(int strength, int stamina, std::string musterMove):
    Character("NPCGuard", (grdcontroller = new GuardController(musterMove)),strength,stamina,false)
{
}

char NPCGuard::move()
{
    return moveDirextion = controller->move();
}

string NPCGuard::getTexture() const
{
    return "NPCGuard";
}
