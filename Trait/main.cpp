#include "MainWindow.hpp"
#include <QtWidgets/QApplication>

#include <string>
#include <type_traits>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::char_traits<char>::to_int_type('c');
    std::make_unsigned_t<char> s;

    MainWindow window;
    window.show();

    return app.exec();
}









