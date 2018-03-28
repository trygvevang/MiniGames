#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "tile.h"
#include "jtile.h"
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    JTile * jt = new JTile();
    jt->rotate();
    jt->rotate();
    jt->rotate();
    jt->rotate();
    jt->rotate();

    QApplication a(argc, argv);
    QGraphicsScene * scene = new QGraphicsScene();

    int w = 800, h = 600;
    scene->setSceneRect(0, 0, w, h);

    QGraphicsView * view = new QGraphicsView(scene);
    view->setFixedSize(w, h);
    view->show();

    return a.exec();
}
