#include "MainWindow.hpp"
#include <QtWidgets/QApplication>

#include <string>
#include <type_traits>

#include <string>
#include <exception>
#include <stdexcept>

void exception_handle_detail()noexcept(true);

void excetpion_handle_std(const std::exception &arg) noexcept(true){
    try {

        std::rethrow_if_nested(arg);
    }
    catch (...) {
        exception_handle_detail();
    }
}

void exception_handle_unknow() {

    try {

    }
    catch (...) {
    }

}

void exception_handle_detail()noexcept(true) {
    try {
        std::rethrow_exception(std::current_exception());
    }
    catch (...) {
        exception_handle_unknow();
    }
}

void exception_handle(
    std::exception_ptr argException,
    const std::string &argWhere,
    const std::string &argWhat
)noexcept(true) {

    try {

        std::rethrow_exception(argException);
    }
    catch(...){
        exception_handle_detail();
    }

}

void xfoo() {}

void(*foo)()noexcept(true);


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //foo=&xfoo;

    std::char_traits<char>::to_int_type('c');
    std::make_unsigned_t<char> s;

    MainWindow window;
    window.show();

    return app.exec();
}









