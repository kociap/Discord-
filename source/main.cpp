#include <QApplication>
//#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING // Doesn't silence STL4009 warnings caused by dependencies
#include "driftuistyle.h"
#include "mainwindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app{argc, argv};
    QApplication::setStyle(new DriftUIStyle(DriftUIStyle::Dark));
    MainWindow mw;
    mw.show();
    return app.exec();
}
