#include "studialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StuDialog w;
    w.show();
    return a.exec();
}
