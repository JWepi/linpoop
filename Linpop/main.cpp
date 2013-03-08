#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    MainWindow      w;

    w.show();
    std::cout << std::endl;
    
    return a.exec();
}
