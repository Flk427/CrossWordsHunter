#include "SearchConjunction.h"
#include <QThread>
#include "core/WordsOccurence.h"
#include "core/DocumentsStorage.h"
#include "gui/ProgressBarWidget.h"

SearchConjunction::SearchConjunction() : QObject(nullptr)
{
}

SearchConjunction::~SearchConjunction()
{
}

void SearchConjunction::start(MainWindow* owner)
{
	QThread* searchThread = new QThread(owner);
	WordsOccurence* wordFinder = new WordsOccurence(DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Event),
													DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Journal),
													nullptr);

	ProgressBarWidget* progressBarWidget = new ProgressBarWidget(owner);

	connect(progressBarWidget, &ProgressBarWidget::closed, wordFinder, &WordsOccurence::stop, Qt::ConnectionType::DirectConnection);
	progressBarWidget->setWindowTitle("Идёт поиск...");
	progressBarWidget->setParent(owner);
	progressBarWidget->setWindowFlags(Qt::Dialog);
	progressBarWidget->setWindowModality(Qt::WindowModality::WindowModal);
	progressBarWidget->show();

	wordFinder->moveToThread(searchThread);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, wordFinder, &WordsOccurence::process);

	connect(wordFinder, &WordsOccurence::progress, progressBarWidget, &ProgressBarWidget::setState);
	connect(wordFinder, &WordsOccurence::wordsFound, owner, &MainWindow::setupOccurenceTable, Qt::ConnectionType::DirectConnection);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(wordFinder, &WordsOccurence::finished, searchThread, &QThread::quit);
	connect(wordFinder, &WordsOccurence::finished, wordFinder, &WordsOccurence::deleteLater);
	connect(wordFinder, &WordsOccurence::finished, progressBarWidget, &QWidget::hide);
	connect(wordFinder, &WordsOccurence::finished, owner, &MainWindow::showOccurenceTable);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &QThread::deleteLater);
	// Удаляем прогрессбар.
	connect(searchThread, &QThread::finished, progressBarWidget, &ProgressBarWidget::deleteLater);
	// Удаляем сами себя.
	connect(searchThread, &QThread::finished, this, &SearchConjunction::deleteLater);

	searchThread->start();
}
