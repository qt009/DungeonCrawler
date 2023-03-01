#include "npc.h"
NPC::NPC(const string &texture, Controller *controller) : Character(texture, controller)
{}

NPC::NPC(const std::string &texture, int strength, int stamina, Controller *controller)
    :Character(texture,controller, strength, stamina)
{
    isNPC = true;
}
string NPC::getTexture() const
{
    return "NPC";
}

char NPC::move()
{
    return moveDirextion = controller->move();
}
