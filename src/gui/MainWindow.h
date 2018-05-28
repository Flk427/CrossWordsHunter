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
	void on_actiontest_qax_triggered();
	void on_actiontest_mime_triggered();
	void on_actiontest_Excel_1_triggered();
	void on_actiontest_Libre_Office_triggered();
	void on_actionImportEventsOO_triggered();
	void on_actionImportJournalsOO_triggered();
	void on_actionImportEventsMSO_triggered();
	void on_actionImportJournalsMSO_triggered();
	void on_actiontest_threads_triggered();

private:
	Ui::MainWindow *ui;
	SearchWordDialog* m_searchWordDialog;
};

#endif // MAINWINDOW_H
