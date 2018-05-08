#include <QCoreApplication>
#include"gameengine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameEngine engine;

    return a.exec();
}
