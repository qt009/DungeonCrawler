#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "abstraktui.h"
#include "controller.h"
#include "startscreen.h"
#include "mainwindow.h"

#include <QPixmap>
#include <vector>

namespace Ui {
class GraphicalUI;
}

class DungeonCrawler;
class GraphicalUI : public AbstraktUI, public Controller
{
public:
    explicit GraphicalUI(QString path, DungeonCrawler* dg);
    ~GraphicalUI();

    QPixmap BloodyFrame;
    QPixmap startScreenIm;
    QPixmap NewGameButton;
    QPixmap PitIm;
    QPixmap RampIm;
    QPixmap SwichtIm;
    QPixmap WallIm;
    QPixmap ChessIm;
    QPixmap LvlChangerImg;
    std::vector<QPixmap> arrows;
    std::vector<std::vector<QPixmap>> chars;
    std::vector<QPixmap> doors;
    std::vector<QPixmap> floors;
    std::vector<QPixmap> portals;
    std::vector<QPixmap> zombies;

    void draw(Level* level) override;
    char move() override;

    void switchWindow();

    void insertQPixMap();
    void insertArrow();
    void insertChar();
    void insertDoor();
    void insertFloor();
    void insertPortal();
    void insertZombie();

    bool checkIfGameEnd(Level* level);

    DungeonCrawler* getDungeonCrawler();
    MainWindow *getMainWindow() const;

    const QString &getPath() const;

private:
    QString path;
    StartScreen *startscreen;
    MainWindow* mainWindow;
    DungeonCrawler* dungeonCraw;
};

#endif // GRAPHICALUI_H
