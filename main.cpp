#include "socketserveur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    socketServeur w;
    w.show();
    return a.exec();
}
