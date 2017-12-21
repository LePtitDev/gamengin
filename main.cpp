#include "src/glwidget.h"
#include "src/gameobject/gameobject.h"
#include "src/script/lua.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    w.showMaximized();

    return a.exec();
}
