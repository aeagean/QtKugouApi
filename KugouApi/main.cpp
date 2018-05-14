#include "WebApi/WebApiTest.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebApiTest *api = new WebApiTest;

    return a.exec();
}
