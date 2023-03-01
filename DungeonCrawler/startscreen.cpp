#include "startscreen.h"
#include "ui_startscreen.h"
#include "graphicalui.h"

StartScreen::StartScreen(GraphicalUI* Gui, QWidget *parent):
    QDialog(parent),
    ui(new Ui::StartScreen),
    gui(Gui)
{
    QString path = gui->getPath();
    ui->setupUi(this);
    ui->label->setStyleSheet("background-color: black;");

    QPixmap BackGroundIm(path + "textures/startscreen.png");
    QPixmap PushButtonIm(path + "textures/new_game_button.png");
    ui->label->setPixmap(BackGroundIm);
    ui->label->setScaledContents(true);
    ui->pushButton->setIcon(QIcon(PushButtonIm));
    ui->pushButton->setStyleSheet("border:none");
    connect(ui->pushButton, &QPushButton::clicked, this, &StartScreen::clickedNewGame);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::clickedNewGame()
{
    gui->switchWindow();
}
