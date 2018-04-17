#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mainmenu.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu mainMenuWindow;
    mainMenuWindow.show();

    return a.exec();
}
