#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>
#include "gui/SearchWordDialog.h"

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
	void updateStatus(QString text);
	void setEventsVisible(bool visible);
	void setJournalsVisible(bool visible);
	void showSearchWordForm(const QString& word="");
	void searchReset();
	void resetDocuments();

private slots:
	void on_actionQuit_triggered();

//	void on_actionLoadEvent_triggered();

private:
	Ui::MainWindow *ui;

	SearchWordDialog* m_searchWordDialog;
};

#endif // MAINWINDOW_H
