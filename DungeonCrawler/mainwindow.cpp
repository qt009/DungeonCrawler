#include "mainwindow.h"
#include "dungeoncrawler.h"
#include "ui_mainwindow.h"
#include "graphicalui.h"
#include "button.h"
#include "portal.h"
#include "level.h"
#include "npc.h"
#include "player.h"
#include "npcguard.h"
#include "door.h"
#include "pit.h"
#include <QMessageBox>
#include <random>

MainWindow::MainWindow(GraphicalUI *gui, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gui(gui)
{
    QString path = gui->getPath();
    ui->setupUi(this);
    //ui->centralwidget->setStyleSheet("background-color: black;");
    //ui->statusbar->setStyleSheet("background-color: black;");
    ui->label->setStyleSheet("background-color: black;");

    QPixmap bloodyFrame (path + "textures/bloody_frame.png");

    ui->label->setPixmap(bloodyFrame);
    ui->label->setScaledContents(true);
    ui->widget->setLayout(ui->gridLayout);
    ui->widget_2->setLayout(ui->gridLayout_2);
    ui->widget_3->setLayout(ui->gridLayout_3);

    progressbars.resize(3);

    initLevel(gui->getDungeonCrawler()->getLevel());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButton()
{
    QString path = gui->getPath();
    Button* btn1 = new Button('q', ui->widget_2);
    Button* btn2 = new Button('w', ui->widget_2);
    Button* btn3 = new Button('e', ui->widget_2);
    Button* btn4 = new Button('a', ui->widget_2);
    Button* btn5 = new Button('s', ui->widget_2);
    Button* btn6 = new Button('d', ui->widget_2);
    Button* btn7 = new Button('z', ui->widget_2);
    Button* btn8 = new Button('x', ui->widget_2);
    Button* btn9 = new Button('c', ui->widget_2);

    btn1->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3 );
    btn2->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn3->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn4->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn5->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn6->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn7->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn8->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);
    btn9->resize(ui->widget_2->width() / 3, ui->widget_2->height() / 3);

    ui->gridLayout_2->addWidget(btn1,0,0,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn2,0,1,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn3,0,2,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn4,1,0,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn5,1,1,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn6,1,2,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn7,2,0,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn8,2,1,Qt::AlignCenter);
    ui->gridLayout_2->addWidget(btn9,2,2,Qt::AlignCenter);

    QPixmap im1(path + "textures/arrows/arrow_up_left.png");
    QPixmap im2(path + "textures/arrows/arrow_up.png");
    QPixmap im3(path + "textures/arrows/arrow_up_right.png");
    QPixmap im4(path + "textures/arrows/arrow_left.png");
    QPixmap im5(path + "textures/arrows/arrow_skip.png");
    QPixmap im6(path + "textures/arrows/arrow_right.png");
    QPixmap im7(path + "textures/arrows/arrow_down_left.png");
    QPixmap im8(path + "textures/arrows/arrow_down.png");
    QPixmap im9(path + "textures/arrows/arrow_down_right.png");

    QIcon icon1(im1);
    QIcon icon2(im2);
    QIcon icon3(im3);
    QIcon icon4(im4);
    QIcon icon5(im5);
    QIcon icon6(im6);
    QIcon icon7(im7);
    QIcon icon8(im8);
    QIcon icon9(im9);

    btn1->setIcon(icon1);
    btn2->setIcon(icon2);
    btn3->setIcon(icon3);
    btn4->setIcon(icon4);
    btn5->setIcon(icon5);
    btn6->setIcon(icon6);
    btn7->setIcon(icon7);
    btn8->setIcon(icon8);
    btn9->setIcon(icon9);

    btn1->setIconSize( btn1->size() );
    btn2->setIconSize( btn2->size() );
    btn3->setIconSize( btn3->size() );
    btn4->setIconSize( btn4->size() );
    btn5->setIconSize( btn5->size() );
    btn6->setIconSize( btn6->size() );
    btn7->setIconSize( btn7->size() );
    btn8->setIconSize( btn8->size() );
    btn9->setIconSize( btn9->size() );

    btn1->setStyleSheet("border:none");
    btn2->setStyleSheet("border:none");
    btn3->setStyleSheet("border:none");
    btn4->setStyleSheet("border:none");
    btn5->setStyleSheet("border:none");
    btn6->setStyleSheet("border:none");
    btn7->setStyleSheet("border:none");
    btn8->setStyleSheet("border:none");
    btn9->setStyleSheet("border:none");
}

void MainWindow::connectButtons()
{
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(0,0)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(0,1)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(0,2)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(1,0)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(1,1)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(1,2)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(2,0)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(2,1)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
    connect(qobject_cast<Button*>(ui->gridLayout_2->itemAtPosition(2,2)->widget()), &Button::clickButton, this, &MainWindow::moveSlot);
}

void MainWindow::initLevel(Level* level)
{
    //auto level = gui->getDungeonCrawler()->getLevel();
    int row = level->getHohe()+2;
    int col = level->getBreite()+2;
    fieldRow = row;
    fieldCol = col;
    //labelField.resize(row, std::vector<QLabel*>(col));
    labelField.resize(12, std::vector<QLabel*>(12));
    charlabels.resize(1);
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            label = new QLabel(ui->widget);
            Tile* tile = level->getTile(i,j);
            if(tile->getTexture() == "Floor"){
                addFloor(label,i,j);
            }
            if(tile->getTexture() == "Wall"){
                label->setPixmap(gui->WallIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Portal"){
                auto port = dynamic_cast<Portal*>(tile);
                addPortal(label,port,i,j);
            }
            if(tile->getTexture() == "CloseDoor"){
                label->setPixmap(gui->doors[0]);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "OpenDoor"){
                label->setPixmap(gui->doors[1]);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Switch"){
                label->setPixmap(gui->SwichtIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Pit"){
                label->setPixmap(gui->PitIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Ramp"){
                label->setPixmap(gui->RampIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "LevelChanger"){
                label->setPixmap(gui->LvlChangerImg);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->getTexture() == "Chest"){
                label->setPixmap(gui->ChessIm);
                labelField.at(i).at(j) = label;
                ui->gridLayout->addWidget(label,i,j,Qt::AlignCenter);
            }
            if(tile->hasCharacter())
            {
                QLabel* character = new QLabel(labelField.at(i).at(j));
                if(tile->getCharacter()->getTexture() == "Player"){
                    character->setPixmap(gui->chars[1][1]);
                    if(!gui->getDungeonCrawler()->getHasChangedLevel()){
                        initProgressBar(tile->getCharacter());
                    }
                }
                else{
                    //charIm = gui->zombies[1];
                    character->setPixmap(gui->zombies[1]);
                }
                character->setScaledContents(true);
                character->setStyleSheet("background-color: transparent;");
                character->resize(labelField.at(i).at(j)->width()-10,labelField.at(i).at(j)->height()+10);
                character->raise();
                character->show();
                charLabelsList.push_back(std::make_pair(tile->getCharacter(),character));
                ui->gridLayout->addWidget(character,i,j,Qt::AlignCenter);
            }
            label->setScaledContents(true);
            label->setMaximumHeight(ui->widget->height() / row );
            label->setMaximumWidth(ui->widget->width() / col );
        }
    }

}

void MainWindow::addFloor(QLabel* label, int row, int col)
{
    std::random_device dev;
    std::mt19937 rd(dev());
    std::uniform_int_distribution<int> dis(0,4);
    int i = dis(rd);

    label->setPixmap(gui->floors[i]);
    labelField.at(row).at(col) = label;
    ui->gridLayout->addWidget(label,row,col,Qt::AlignCenter);
}

void MainWindow::addPortal(QLabel* label, Portal* port, int row, int col)
{
    int typePort = port->getTypePortal();
    label->setPixmap(gui->portals[typePort]);
    labelField.at(row).at(col) = label;
    ui->gridLayout->addWidget(label,row,col,Qt::AlignCenter);
}

void MainWindow::setInputChanged(bool status)
{
    inputChanged = status;
}

bool MainWindow::hasInputChanged()
{
    return inputChanged;
}

char MainWindow::getLastInput()
{
    return lastInput;
}

void MainWindow::updateCharacter()
{
    std::random_device dev;
    std::mt19937 rd(dev());
    for(auto pair : charLabelsList){
        Character* character = pair.first;
        QLabel* characterLabel = pair.second;
        if(typeid(*character) == typeid(Player)){
            Tile* tile = character->getTile();
            auto i = tile->getRow();
            auto j = tile->getCol();
            std::uniform_int_distribution<std::mt19937::result_type> dis(0,2);

            //char moveDirection = tile->getCharacter()->getMoveDirection();
            char moveDirection = character->getMoveDirection();
            characterLabel->setParent(labelField.at(i).at(j));
            characterLabel->move(QPoint(0,0));
            switch(moveDirection)
            {
            case 'q':
            case 'w':
            case 'e':
            {
                characterLabel->setPixmap(gui->chars[0][dis(rd)]);
                break;
            }
            case 'a':
            {
                characterLabel->setPixmap(gui->chars[2][dis(rd)]);
                break;
            }
            case 'd':
            {
                characterLabel->setPixmap(gui->chars[3][dis(rd)]);
                break;
            }
            case 'z':
            case 'x':
            case 'c':
            {
                characterLabel->setPixmap(gui->chars[1][dis(rd)]);
                break;
            }
            }
            if(typeid(*tile) == typeid(Pit)){
                labelField.at(i).at(j)->setStyleSheet("background-color: transparent;");
                characterLabel->setParent(this);
                characterLabel->move(ui->gridLayoutWidget->pos() + labelField.at(i).at(j)->pos()+ QPoint(20, 100));
                characterLabel->lower();
                labelField.at(i).at(j)->raise();
            }
            characterLabel->show();
            updatePlayerStatus(character->getHitpoints(), character->getStamina(), character->getStrength());
        }
        else if(typeid(*character) == typeid(NPC)||typeid(*character) == typeid(NPCGuard)){
            Tile* tile = character->getTile();
            auto i = tile->getRow();
            auto j = tile->getCol();
            //char moveDirection = tile->getCharacter()->getMoveDirection();
            char moveDirection = character->getMoveDirection();
            characterLabel->setParent(labelField.at(i).at(j));
            characterLabel->move(QPoint(0,0));
            switch(moveDirection)
            {
            case 'q':
            case 'a':
            case 'z':
            case 'w':
            {
                characterLabel->setPixmap(gui->zombies[0]);
                break;
            }
            case 'x':
            case 'e':
            case 'd':
            case 'c':
            {
                characterLabel->setPixmap(gui->zombies[1]);
                break;
            }
            }
            if(typeid(*tile) == typeid(Pit)){
                labelField.at(i).at(j)->setStyleSheet("background-color: transparent;");
                labelField.at(i).at(j)->raise();

                characterLabel->setParent(this);
                characterLabel->move(ui->gridLayoutWidget->pos() + labelField.at(i).at(j)->pos()+ QPoint(20, 100));
                characterLabel->lower();
            }
            characterLabel->show();
        }
    }
}

void MainWindow::updatePlayerStatus(int hp, int sta, int stre)
{
    progressbars[0]->setValue(stre);
    progressbars[0]->setFormat(QString::number(progressbars[0]->value()));

    progressbars[1]->setValue(sta);
    progressbars[1]->setFormat(QString::number(progressbars[1]->value()));

    progressbars[2]->setValue(hp);
    progressbars[2]->setFormat(QString::number(progressbars[2]->value()));
}

void MainWindow::draw(Level *level)
{
    if(gui->getDungeonCrawler()->getHasChangedLevel()){

        for(int i=0; i < fieldRow; i++){
            for (int j=0; j < fieldCol;j++){
                delete labelField[i][j];
                charLabelsList.clear();
                delete ui->gridLayout->itemAtPosition(i,j);
            }
        }
        this->initLevel(level);
        gui->getDungeonCrawler()->setHasChangedLevel(false);
    }
    updateCharacterList();
    Character* thatCharacter = nullptr;
    Character* thePlayer = nullptr;
    int row = fieldRow = level->getHohe()+2;
    int col = fieldCol =level->getBreite()+2;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            Tile* tile = level->getTile(i,j);

            if(tile->hasCharacter())
            {
                thatCharacter = tile->getCharacter();
                if(!thatCharacter->getIsNPC()) thePlayer = thatCharacter;
                updateCharacter();

            }

            if(typeid(*tile) == typeid(Door))
            {
                Door* door = dynamic_cast<Door*>(tile);
                QLabel* doorLabel = labelField.at(i).at(j);
                if(door->isOpend()){
                    doorLabel->setPixmap(gui->doors[1]);
                } else{
                    doorLabel->setPixmap(gui->doors[0]);
                }
            }
        }
    }
    if(thePlayer!=nullptr){
        progressbars[0]->setValue(thePlayer->getStrength());
        progressbars[0]->setFormat(QString::number(progressbars[0]->value()));

        progressbars[1]->setValue(thePlayer->getStamina());
        progressbars[1]->setFormat(QString::number(progressbars[1]->value()));

        progressbars[2]->setValue(thePlayer->getHitpoints());
        progressbars[2]->setFormat(QString::number(progressbars[2]->value()));
    }
}
void MainWindow::updateCharacterList()
{
    for(auto pair : charLabelsList){
        if(!pair.first->getIsAlive()){
            delete pair.second;
            charLabelsList.erase(std::remove(charLabelsList.begin(), charLabelsList.end(), pair), charLabelsList.end());
        }
    }
}

bool MainWindow::checkIfGameEnd(Level *level)
{
    if(level->hasPlayerWin()){
        QMessageBox::information(this,tr("Congratulation"),tr("Thanks for playing"));
        return true;
    }
    if(level->hasPlayerLose()){
        QMessageBox::information(this,tr("Opps"),tr("You have lost!"));
        return true;
    }
    return false;
}

void MainWindow::initProgressBar(Character *character)
{
    progressbars[0] = new QProgressBar(ui->widget_3);
    progressbars[1] = new QProgressBar(ui->widget_3);
    progressbars[2] = new QProgressBar(ui->widget_3);

    QProgressBar* p1 = progressbars[0];
    QProgressBar* p2 = progressbars[1];
    QProgressBar* p3 = progressbars[2];

    p1->setRange(0, character->getStrength());
    p2->setRange(0, character->getStamina());
    p3->setRange(0, character->getHitpoints());

    p1->setValue(p1->maximum());
    p2->setValue(p2->maximum());
    p3->setValue(p3->maximum());

    QLabel* l1 = new QLabel(ui->widget_3);
    QLabel* l2 = new QLabel(ui->widget_3);
    QLabel* l3 = new QLabel(ui->widget_3);

    l1->setText("Strength");
    l2->setText("Stamina");
    l3->setText("Hitpoints");

    p1->setFormat(QString::number(p1->value()));
    p2->setFormat(QString::number(p2->value()));
    p3->setFormat(QString::number(p3->value()));

    l1->setStyleSheet("background-color: grey;");
    l2->setStyleSheet("background-color: grey;");
    l3->setStyleSheet("background-color: grey;");


    ui->gridLayout_3->addWidget(p1,0,0,Qt::AlignCenter);
    ui->gridLayout_3->addWidget(l1,0,1,Qt::AlignCenter);
    ui->gridLayout_3->addWidget(p2,1,0,Qt::AlignCenter);
    ui->gridLayout_3->addWidget(l2,1,1,Qt::AlignCenter);
    ui->gridLayout_3->addWidget(p3,2,0,Qt::AlignCenter);
    ui->gridLayout_3->addWidget(l3,2,1,Qt::AlignCenter);
}

Ui::MainWindow *MainWindow::getUI()
{
    return ui;
}

void MainWindow::moveSlot(char move)
{
    lastInput=move;
    inputChanged=true;
}
