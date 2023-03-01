#include "graphicalui.h"
//#include "ui_graphicalui.h"
#include "ui_mainwindow.h"
#include "dungeoncrawler.h"
#include <QPushButton>
#include <QtTest/QTest>

GraphicalUI::GraphicalUI(QString path, DungeonCrawler* dg): AbstraktUI(), Controller(), path(path), dungeonCraw(dg)
{
    insertQPixMap();

    startscreen = new class StartScreen(this);
    mainWindow = new class MainWindow(this);

    mainWindow->setButton();
    mainWindow->connectButtons();
    mainWindow->initProgressBar(dg->getCharacters()[0]);

    startscreen->show();
}

GraphicalUI::~GraphicalUI()
{
}

void GraphicalUI::draw(Level *level)
{
    mainWindow->draw(level);
}


char GraphicalUI::move()
{
    while(1){
        QTest::qWait(50);
        QCoreApplication::processEvents();
        qDebug() << "check";
        if(mainWindow->hasInputChanged()){
            mainWindow->setInputChanged(false);
            qDebug() << mainWindow->getLastInput();
            return mainWindow->getLastInput();
        }
    }
}

void GraphicalUI::insertQPixMap()
{
    insertArrow();
    insertChar();
    insertDoor();
    insertFloor();
    insertPortal();
    insertZombie();
    BloodyFrame = QPixmap(path + "textures/bloody_frame.png");
    NewGameButton = QPixmap(path + "textures/new_game_button.png");
    startScreenIm = QPixmap(path + "textures/startscreen.png");
    PitIm = QPixmap(path + "textures/pit.png");
    RampIm = QPixmap(path + "textures/ramp.png");
    SwichtIm = QPixmap(path + "textures/switch.png");
    WallIm = QPixmap(path + "textures/wall/wall1.png");
    ChessIm = QPixmap(path + "textures/chest.png");
    LvlChangerImg = QPixmap(path + "textures/levelchanger.png");
}

void GraphicalUI::insertArrow()
{
    arrows.resize(9);
    arrows[0] = QPixmap(path + "textures/arrows/arrow_down_left.png");
    arrows[1] = QPixmap(path + "textures/arrows/arrow_down_right.png");
    arrows[2] = QPixmap(path + "textures/arrows/arrow_down.png");
    arrows[3] = QPixmap(path + "textures/arrows/arrow_left.png");
    arrows[4] = QPixmap(path + "textures/arrows/arrow_right.png");
    arrows[5] = QPixmap(path + "textures/arrows/arrow_skip.png");
    arrows[6] = QPixmap(path + "textures/arrows/arrow_up_left.png");
    arrows[7] = QPixmap(path + "textures/arrows/arrow_up_right.png");
    arrows[8] = QPixmap(path + "textures/arrows/arrow_up.png");
}

void GraphicalUI::insertChar()
{
    chars.resize(4,std::vector<QPixmap>(3));
    //add char back
    chars[0][0] = QPixmap(path + "textures/char/back/char_back_2.png");
    chars[0][1] = QPixmap(path + "textures/char/back/char_back_1.png");
    chars[0][2] = QPixmap(path + "textures/char/back/char_back_3.png");
    //add char front
    chars[1][0] = QPixmap(path + "textures/char/front/char_front_2.png");
    chars[1][1] = QPixmap(path + "textures/char/front/char_front_1.png");
    chars[1][2] = QPixmap(path + "textures/char/front/char_front_3.png");
    //add char left
    chars[2][0] = QPixmap(path + "textures/char/left/char_left_2.png");
    chars[2][1] = QPixmap(path + "textures/char/left/char_left_1.png");
    chars[2][2] = QPixmap(path + "textures/char/left/char_left_3.png");
    //add char right
    chars[3][0] = QPixmap(path + "textures/char/right/char_right_2.png");
    chars[3][1] = QPixmap(path + "textures/char/right/char_right_1.png");
    chars[3][2] = QPixmap(path + "textures/char/right/char_right_3.png");
}

void GraphicalUI::insertDoor()
{
    doors.resize(2);
    doors[0] = QPixmap(path + "textures/doors/door1.png");
    doors[1] = QPixmap(path + "textures/doors/door2.png");
}

void GraphicalUI::insertFloor()
{
    floors.resize(5);
    floors[0] = QPixmap(path + "textures/floor/floor1.png");
    floors[1] = QPixmap(path + "textures/floor/floor2.png");
    floors[2] = QPixmap(path + "textures/floor/floor3.png");
    floors[3] = QPixmap(path + "textures/floor/floor4.png");
    floors[4] = QPixmap(path + "textures/floor/floor5.png");
}

void GraphicalUI::insertPortal()
{
    portals.resize(3);
    portals[0] = QPixmap(path + "textures/portal/portal1.png");
    portals[1] = QPixmap(path + "textures/portal/portal2.png");
    portals[2] = QPixmap(path + "textures/portal/portal3.png");
}

void GraphicalUI::insertZombie()
{
    zombies.resize(2);
    zombies[0] = QPixmap(path + "textures/zombie/zombie_left.png");
    zombies[1] = QPixmap(path + "textures/zombie/zombie_right.png");
}

bool GraphicalUI::checkIfGameEnd(Level *level)
{
    return mainWindow->checkIfGameEnd(level);
}

DungeonCrawler *GraphicalUI::getDungeonCrawler()
{
    return dungeonCraw;
}

MainWindow *GraphicalUI::getMainWindow() const
{
    return mainWindow;
}

const QString &GraphicalUI::getPath() const
{
    return path;
}

void GraphicalUI::switchWindow()
{
    startscreen->hide();
    mainWindow->show();
}

