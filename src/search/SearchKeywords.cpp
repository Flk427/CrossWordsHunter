#include "SearchKeywords.h"
#include "thread/KeywordsFinder.h"
#include "core/ApplicationSettings.h"
#include "core/thread/ThreadObject.h"
#include "helpers/GuiHelpers.h"

SearchKeywords::SearchKeywords() : QObject(nullptr)
{
}

SearchKeywords::~SearchKeywords()
{
}

void SearchKeywords::start(MainWindow* owner)
{
	ApplicationSettings::Instance().setSearchWord("");

	KeywordsFinder* wordFinder = new KeywordsFinder();
	ThreadObject* searchThread = new ThreadObject(wordFinder, this);

	createSearchProgressBarWidget(owner, wordFinder);

	// Удаляем сами себя.
	connect(searchThread, &ThreadObject::finished, this, &SearchKeywords::deleteLater);

	searchThread->start();
}
