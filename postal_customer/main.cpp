#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.init_postal_customer_parameters();
    w.setWindowTitle("Postal Customer Application");
    w.start();
    w.show();

    return a.exec();
}
