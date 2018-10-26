#include <QApplication>

#include "driftuistyle.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    QApplication::setStyle(new DriftUIStyle(DriftUIStyle::Dark));
    MainWindow mw;
    mw.show();
    return app.exec();
}
