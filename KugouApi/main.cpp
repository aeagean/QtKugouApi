#include "WebApi/WebApi.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebApi *api = new WebApi;
    api->searchMusics("aa", NULL, "");

    return a.exec();
}
