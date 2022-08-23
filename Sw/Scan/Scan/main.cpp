#include "scan.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scan w;
    w.show();
    return a.exec();
}
