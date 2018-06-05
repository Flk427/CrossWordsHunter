#include "SearchKeywords.h"
#include "thread/KeywordsFinder.h"
#include "core/ApplicationSettings.h"
#include "core/thread/ThreadObject.h"
#include "helpers/GuiHelpers.h"
#include "core/KeywordsListModel.h"

SearchKeywords::SearchKeywords() : QObject(nullptr)
{
}

SearchKeywords::~SearchKeywords()
{
}

void SearchKeywords::start(MainWindow* owner)
{
	// Установка списка слов для навигации по DocumentViewerWidget после поиска.
	ApplicationSettings::Instance().setSearchWords(KeywordsListModel::Instance().keywords());

	KeywordsFinder* wordFinder = new KeywordsFinder();
	ThreadObject* searchThread = new ThreadObject(wordFinder, this);

	createSearchProgressBarWidget(owner, wordFinder);

	// Удаляем сами себя.
	connect(searchThread, &ThreadObject::finished, this, &SearchKeywords::deleteLater);

	searchThread->start();
}
