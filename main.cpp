#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Журнал учета дозовых нагрузок пациента при рентгенологических исследованиях");
    w.show();
    return a.exec();
}
