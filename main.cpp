#include "mainwindow.h"
#include "qhotkey.h"
#include "Windows.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    QHotkey* hotkey = new QHotkey(MOD_ALT, VK_SPACE);
    QHotkey::connect(hotkey, &QHotkey::pressed, w, [=]() {
        w->show();
        qDebug() << "你触发了快捷键";
    });
    int ret = a.exec();
    delete hotkey;
    delete w;
    return ret;
}
