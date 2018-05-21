#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>
#include "core/types.h"
#include "gui/SearchWordDialog.h"
#include "gui/ProgressBarWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void loadNewEvent();
	void loadNewJournal();
	void updateStatus(QString text);
	void setEventsVisible(bool visible);
	void setJournalsVisible(bool visible);
	void searchWord(const QString& word="");
	void searchReset();
	void resetDocuments();
	void setupOccurenceTable(const CWTypes::WordsOccuring* wordsOccuring);
	void showOccurenceTable();

private slots:
	void on_actionQuit_triggered();
	void searchConjunction();
	void searchKeywords();

//	void on_actionLoadEvent_triggered();

private:
	Ui::MainWindow *ui;
	SearchWordDialog* m_searchWordDialog;
	ProgressBarWidget m_pb;
};

#endif // MAINWINDOW_H
