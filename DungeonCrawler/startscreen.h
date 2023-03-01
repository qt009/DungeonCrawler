#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class StartScreen;
}

class GraphicalUI;
class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(GraphicalUI* Gui, QWidget *parent = nullptr);
    ~StartScreen();

public slots:
    void clickedNewGame();

private:
    Ui::StartScreen *ui;
    QPushButton *pushButton;
    GraphicalUI* gui;
};

#endif // STARTSCREEN_H
