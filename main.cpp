#include "fpucalculator.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FPUCalculator w;
    w.show();

    return a.exec();
}
