#include "SearchKeywords.h"
#include "core/KeywordsFinder.h"

SearchKeywords::SearchKeywords() : QObject(nullptr)
{

}

SearchKeywords::~SearchKeywords()
{

}

void SearchKeywords::start(MainWindow* owner)
{
	QThread* searchThread = new QThread(this);
	KeywordsFinder* wordFinder = new KeywordsFinder(nullptr);

	ProgressBarWidget* progressBarWidget = new ProgressBarWidget(owner);

	connect(wordFinder, &KeywordsFinder::reportState, progressBarWidget, &ProgressBarWidget::setState);
	progressBarWidget->setWindowTitle("Идёт поиск...");
	progressBarWidget->setParent(owner);
	progressBarWidget->setWindowFlags(Qt::Dialog);
	progressBarWidget->setWindowModality(Qt::WindowModality::WindowModal);
	progressBarWidget->show();

	wordFinder->moveToThread(searchThread);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, wordFinder, &KeywordsFinder::process);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(wordFinder, &KeywordsFinder::finished, searchThread, &QThread::quit);
	connect(wordFinder, &KeywordsFinder::finished, wordFinder, &KeywordsFinder::deleteLater);
	connect(wordFinder, &KeywordsFinder::finished, progressBarWidget, &QWidget::hide);

	connect(progressBarWidget, &ProgressBarWidget::closed, wordFinder, &KeywordsFinder::stop, Qt::ConnectionType::DirectConnection);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &QThread::deleteLater);
	// Удаляем прогрессбар.
	connect(searchThread, &QThread::finished, progressBarWidget, &ProgressBarWidget::deleteLater);
	// Удаляем сами себя.
	connect(searchThread, &QThread::finished, this, &SearchKeywords::queueDelete);

	//connect(wordFinder, &WordsOccurence::wordsFound, ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::setItems, Qt::ConnectionType::DirectConnection);

	searchThread->start();
}

void SearchKeywords::queueDelete()
{
	deleteLater();
}
