#include "MainWindow.hpp"
#include <QtWidgets/QApplication>

#include <string>
#include <type_traits>

#include<iostream>
#include"part_goole_v8/include/double-conversion/double-conversion.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto & c=
        double_conversion::DoubleToStringConverter::EcmaScriptConverter();

    char test_ans[256]={};
    double_conversion::StringBuilder b(test_ans,256);

    c.ToShortest(
        -1222.123456789,
        &b
    );

    std::cout<<b.position()<<std::endl;
    b.Finalize();
    std::cout<<b.size()<<std::endl;

    MainWindow window;
    window.show();

    return app.exec();
}









