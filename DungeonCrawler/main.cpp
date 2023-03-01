#include "graphicalui.h"
#include "level.h"
#include "dungeoncrawler.h"
#include "list.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    DungeonCrawler* d = new DungeonCrawler();
    d->play();
    delete d;
    return a.exec();
}
