#ifndef SEARCHWORDDIALOG_H
#define SEARCHWORDDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QThread>
#include "core/WordFinder.h"

namespace Ui {
class SearchWordDialog;
}

/*!
\brief Поиск слова.

Вызываемые потоки сохраняют результаты сразу в DocumentsStorage.
*/
class SearchWordDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SearchWordDialog(QWidget *parent = 0);
	~SearchWordDialog();

	void startSearchWord(const QString& word);

private slots:
	void startSearch();
	void journalsSearchThreadStart();
	void searchFinished();

private:
	Ui::SearchWordDialog *ui;
	QThread* m_eventsSearchThread;
	QThread* m_journalsSearchThread;
	WordFinder* m_eventsWordFinder;
	WordFinder* m_journalsWordFinder;
	bool m_canClose;

	virtual int exec() override;

	void createSearchThread(const CWTypes::DocumentType documentType, QThread*& searchThread, WordFinder*& wordFinder, const QString& path, const QString& word, bool nextThread);

	// QDialog interface
public slots:
	virtual int exec(const QStringList& keywords);
	void incrementProgressBarPosition();

	// QWidget interface
protected:
	virtual void closeEvent(QCloseEvent* event) override;
};

#endif // SEARCHWORDDIALOG_H
