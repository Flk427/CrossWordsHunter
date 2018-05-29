#include "SearchConjunction.h"
#include <QThread>
#include "thread/WordsOccurence.h"
#include "core/DocumentsStorage.h"
#include "core/thread/ThreadObject.h"
#include "helpers/GuiHelpers.h"

SearchConjunction::SearchConjunction() : QObject(nullptr)
{
}

SearchConjunction::~SearchConjunction()
{
}

void SearchConjunction::start(MainWindow* owner)
{
	WordsOccurence* wordFinder = new WordsOccurence(DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Event),
													DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Journal));
	ThreadObject* searchThread = new ThreadObject(wordFinder, this);

	createSearchProgressBarWidget(owner, wordFinder);

	// Удаляем сами себя.
	connect(searchThread, &ThreadObject::finished, this, &SearchConjunction::deleteLater);

	connect(wordFinder, &WordsOccurence::wordsFound, owner, &MainWindow::setupOccurenceTable, Qt::ConnectionType::DirectConnection);
	connect(wordFinder, &WordsOccurence::finished, owner, &MainWindow::showOccurenceTable);

	searchThread->start();
}
