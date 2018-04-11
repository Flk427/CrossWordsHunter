#include <QApplication>
#include <QDebug>
#include <QWidget>
#include <iostream>
#include <Windows.h>
#include <gui/MainWindow.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	return a.exec();
}
