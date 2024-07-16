#include "mainwindow.h"
#include <QApplication>
#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator calc;
    calc.resize(600,500);
    calc.show();
    return a.exec();
}
