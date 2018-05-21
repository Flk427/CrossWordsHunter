#include <QApplication>
#include <QDebug>
#include <QWidget>
#include <iostream>
#include <Windows.h>
#include <gui/MainWindow.h>

/*!
\brief main
\param argc
\param argv
\return int

\todo Выводить кол-во найденных слов.
\todo Редактор списка ключевых слов.
\todo Пакетная загрузка из MSO.
\todo При загрузке документа проверять на наличие ключевых слов.
\todo Поиск пред./след. ключевого слова.
*/
int main(int argc, char *argv[])
{
	qRegisterMetaType<QVector<int>>("QVector<int>");

	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	return a.exec();
}
