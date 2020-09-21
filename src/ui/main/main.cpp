#include <ui/forms/mainform.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm widget;
    return a.exec();

    //MainWindow w;
    //w.setObjectName("Main");
    //w.show();
    //return a.exec();
}
