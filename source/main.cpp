#include <QApplication>

#include "driftuistyle.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
	QApplication app{argc, argv};
	MainWindow mw;
	DriftUIStyle style;
	mw.setStyle(&style);
	mw.show();
	return app.exec();
}