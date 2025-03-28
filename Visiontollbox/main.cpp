#include "Visiontollbox.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Visiontollbox w;
    w.show();
    return a.exec();
}
