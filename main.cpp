#include <QApplication>
#include "MainWindows.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-color:#494b52;");
    w.setWindowTitle("Deck Builder");
    w.show();
    return a.exec();
}