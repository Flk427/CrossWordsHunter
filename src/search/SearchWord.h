#ifndef SEARCHWORD_H
#define SEARCHWORD_H

#include <QObject>
#include "gui/MainWindow.h"
#include "thread/WordFinder.h"

/*!
\brief The SearchWord class

Вызываемые потоки сохраняют результаты сразу в DocumentsStorage.
*/
class SearchWord : public QObject
{
	Q_OBJECT
public:
	explicit SearchWord(QObject *parent = nullptr);
	virtual ~SearchWord();

	void start(MainWindow* owner, const QString& word);

private:
	ProgressBarWidget* m_pb;
	QThread* m_eventsSearchThread;
	QThread* m_journalsSearchThread;
	WordFinder* m_eventsWordFinder;
	WordFinder* m_journalsWordFinder;

	void createSearchThread(const CWTypes::DocumentType documentType, QThread*& searchThread, WordFinder*& wordFinder, const QString& path, const QString& word, bool nextThread);
	void journalsSearchThreadStart();

};

#endif // SEARCHWORD_H
