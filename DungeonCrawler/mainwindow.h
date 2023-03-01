#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <vector>
#include <QProgressBar>

namespace Ui {
class MainWindow;
}

class Level;
class Character;
class Portal;
class GraphicalUI;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(GraphicalUI* gui, QWidget *parent = nullptr);
    ~MainWindow();

    void setButton();
    void connectButtons();
    void setInputChanged(bool status);
    bool hasInputChanged();
    char getLastInput();
    void updateCharacter();
    void updatePlayerStatus(int, int, int);
    void updateCharacterList();
    bool checkIfGameEnd(Level* level);

    void draw(Level* level);

    void initProgressBar(Character* character);
    void initLevel(Level* level);
    void addFloor(QLabel* label, int row, int col);
    void addPortal(QLabel* label, Portal* port, int row, int col);

    Ui::MainWindow* getUI();

public slots:
    void moveSlot(char move);
private:
    Ui::MainWindow *ui;
    GraphicalUI* gui;
    QLabel* label;
    std::vector<std::vector<QLabel*>> labelField;
    std::vector<std::pair<Character*, QLabel*>> charLabelsList;
    std::vector<QLabel*> charlabels;
    std::vector<QProgressBar*> progressbars;
    int fieldRow;
    int fieldCol;
    bool inputChanged;
    char lastInput;
};

#endif // MAINWINDOW_H
