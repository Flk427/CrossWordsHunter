#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void loadNewEvent();
	void loadNewJournal();
	void statusUpdate(QString text);
	void eventsVisible(bool visible);
	void journalsVisible(bool visible);

private slots:
	void on_actionQuit_triggered();

//	void on_actionLoadEvent_triggered();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
