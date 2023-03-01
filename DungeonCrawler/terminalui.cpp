#include <iostream>
#include "terminalui.h"

using namespace std;

TerminalUI::TerminalUI(): AbstraktUI(), Controller()
{
}

void TerminalUI::draw(Level* level)
{
    for (int i = 0; i < level->Hohe+2; i++){
        //cout << "|" ;
        for (int j = 0; j < level->Breite+2; j++){
            Tile* currentTile = level->Spielfeld[i][j];
            if (currentTile->hasCharacter()){
                cout << " X ";
            }
            else if (currentTile->getTexture() == "Floor"){
                cout << " . ";
            }
            else if (currentTile->getTexture() == "Wall"){
                cout << " # ";
            }
            else if (currentTile->getTexture() == "Portal"){
                cout << " O ";
            }
            else if (currentTile->getTexture() == "OpenDoor"){
                cout << " / ";
            }
            else if (currentTile->getTexture() == "CloseDoor"){
                cout << " D ";
            }
            else if (currentTile->getTexture() == "Switch"){
                cout << " ? ";
            }
            else if (currentTile->getTexture() == "Pit"){
                cout << " * ";
            }
            else if (currentTile->getTexture() == "Ramp"){
                cout << " = ";
            }
            else if (currentTile->getTexture() == "LevelChanger"){
                cout<<" L ";
            }
            else if (currentTile->getTexture() == "NPC"){
                cout<<" N ";
            }
            else if (currentTile->getTexture() == "NPCGuard"){
                cout<<" N ";
            }
        }
        cout << endl;
    }
}

Level* TerminalUI::setUpSpielfeld()
{
    int breite, hohe;
    cout << "Geben Sie die Hoehe und die Breite des Spiels ein: ";
    cin >> breite >> hohe;
    if (breite==0||hohe==0){
        return new Level();
    }
    return new Level(breite, hohe);
}

char TerminalUI::move()
{
    cout << "Eingabe zur Bewegung (nur char): ";
    char eingabe;
    cin >> eingabe;
    return eingabe;
}
