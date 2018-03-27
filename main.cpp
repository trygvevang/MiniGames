#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene * scene = new QGraphicsScene();

    int w = 800, h = 600;
    scene->setSceneRect(0, 0, w, h);

    QGraphicsView * view = new QGraphicsView(scene);
    view->setFixedSize(w, h);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    return a.exec();
}
