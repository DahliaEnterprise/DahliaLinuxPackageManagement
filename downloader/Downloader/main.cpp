#include <QCoreApplication>
#include "head.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    head* h = new head();
    h->start();

    return a.exec();
}
