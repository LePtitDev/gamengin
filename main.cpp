#include "src/mainwindow.h"
#include "src/gameobject/gameobject.h"
#include "src/script/lua.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    LuaScript scr;
    scr.load("a = 'un test'");
    scr.execute();
    std::string s;
    qInfo() << scr.getVariable("a", s);
    qInfo() << s.c_str();

    return a.exec();
}
