#include <QCoreApplication>
#include "head.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Initalize the thinker.
    head* h = new head();
    //Start
    h->start();
    //Return status code
    return a.exec();
}
