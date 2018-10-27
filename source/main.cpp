#include <QApplication>

#include "driftuistyle.h"
#include "mainwindow.h"

// https://discordapp.com/api/oauth2/authorize?client_id=505720390820167690&redirect_uri=https%3A%2F%2Fgithub.com%2Fkociap%2FDiscordpp&response_type=code&scope=identify

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    QApplication::setStyle(new DriftUIStyle(DriftUIStyle::Dark));
    MainWindow mw;
    mw.show();
    return app.exec();
}
