#include <QApplication>
//#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING // Doesn't silence STL4009 warnings caused by dependencies
#include "QFile"
#include "discord/auth.hpp"
#include "loginwindow.hpp"
#include "mainwindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app{argc, argv};

    QFile file{":/style.css"};
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    app.setStyleSheet(style);

    Main_window mw;
    return app.exec();
}
