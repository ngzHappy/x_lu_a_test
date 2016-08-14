#include "MainWindow.hpp"
#include <QtWidgets/QApplication>

#include <string>
#include <type_traits>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    MainWindow window;
    window.show();

    return app.exec();
}









