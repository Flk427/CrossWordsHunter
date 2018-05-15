#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TextEditorDialog.h"
#include "helpers/FilesHelpers.h"
#include "core/DocumentsStorage.h"
#include "core/ApplicationSettings.h"
#include "core/WordsOccurence.h"
#include "core/KeywordsFinder.h"
#include "core/KeywordsListModel.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	setWindowIcon(QIcon(":/img/CrossWordsHunter.ico"));

	m_searchWordDialog = new SearchWordDialog(this);

	ui->setupUi(this);
	setWindowTitle("CrossWordsHunter");

	ui->tabWidget->setCurrentIndex(0);
	ui->wordsOccurenceTableWidget->hide();
	showMaximized();

	ui->eventsViewverWidget->setDocumentType(CWTypes::Event);
	ui->journalsViewverWidget->setDocumentType(CWTypes::Journal);

	ui->eventsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(CWTypes::Event));
	ui->journalsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(CWTypes::Journal));

	connect(ui->toolButton_3, &QToolButton::toggled, ui->eventsViewverWidget, &DocumentsStorageViewverWidget::setVisible);
	connect(ui->toolButton_4, &QToolButton::toggled, ui->journalsViewverWidget, &DocumentsStorageViewverWidget::setVisible);

	connect(&DocumentsStorage::Instance(), &DocumentsStorage::storageUpdatedNotice, this, &MainWindow::updateStatus);
	connect(ui->eventsViewverWidget, &DocumentsStorageViewverWidget::searchSelectedWord, this, &MainWindow::showSearchWordForm);
	connect(ui->journalsViewverWidget, &DocumentsStorageViewverWidget::searchSelectedWord, this, &MainWindow::showSearchWordForm);
	//connect(ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::searchSelectedWord, this, &MainWindow::showSearchWordForm);
	connect(ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::wordSelectionChanged, this, &MainWindow::resetDocuments);

	connect(ui->actionSearchReset, &QAction::triggered, this, &MainWindow::searchReset);
	//connect(ui->actionShowSearchWordForm, &QAction::triggered, this, &MainWindow::showSearchWordForm); // соединил в дизайнере, т.к. типы разные.
	connect(ui->actionSearchConjunction, &QAction::triggered, this, &MainWindow::searchConjunction);
	connect(ui->actionSearchKeywords, &QAction::triggered, this, &MainWindow::searchKeywords);

	connect(ui->actionLoadEvent, &QAction::triggered, this, &MainWindow::loadNewEvent);
	connect(ui->actionLoadJournal, &QAction::triggered, this, &MainWindow::loadNewJournal);

	connect(ui->toolButtonNewEvent, &QToolButton::clicked, this, &MainWindow::loadNewEvent);
	connect(ui->toolButtonNewJournal, &QToolButton::clicked, this, &MainWindow::loadNewJournal);

	DocumentsStorage::Instance().updateDocumentsLists();

	ui->wordsOccurenceTableWidget->setModel(DocumentsStorage::Instance().getWordsOccurenceTableModel());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadNewEvent()
{
	TextEditorDialog editor;

	if (editor.exec() == QDialog::Accepted)
	{
		// acceptEvent
		DocumentsStorage::Instance().addDocument(CWTypes::DocumentType::Event, editor.getTextDocument());
	}
}

void MainWindow::loadNewJournal()
{
	TextEditorDialog editor;

	if (editor.exec() == QDialog::Accepted)
	{
		// acceptJournal
		DocumentsStorage::Instance().addDocument(CWTypes::DocumentType::Journal, editor.getTextDocument());
	}
}

void MainWindow::updateStatus(QString text)
{
	resetDocuments();
	statusBar()->showMessage(text);
}

void MainWindow::setEventsVisible(bool visible)
{
	ui->eventsViewverWidget->setVisible(visible);
}

void MainWindow::setJournalsVisible(bool visible)
{
	ui->journalsViewverWidget->setVisible(visible);
}

void MainWindow::showSearchWordForm(const QString& word)
{
	if (word.isEmpty())
	{
		if (m_searchWordDialog->exec(KeywordsListModel::Instance().keywords()) == QDialog::Accepted)
		{
			ui->wordsOccurenceTableWidget->hide();
			resetDocuments();
			ui->tabWidget->setCurrentIndex(1);
		}
	}
	else
	{
		ui->wordsOccurenceTableWidget->hide();
		resetDocuments();
		m_searchWordDialog->startSearchWord(word);
	}
}

void MainWindow::searchReset()
{
	ui->wordsOccurenceTableWidget->hide();
//	resetDocuments();
	DocumentsStorage::Instance().readDocumentsLists();
	ApplicationSettings::Instance().setSearchWord("");
}

void MainWindow::resetDocuments()
{
	ui->eventsViewverWidget->resetText();
	ui->journalsViewverWidget->resetText();
}

void MainWindow::on_actionQuit_triggered()
{
	// Эта штука автоматически связывается через QMetaObject::connectSlotsByName(MainWindow);
	close();
}

void MainWindow::searchConjunction()
{
//	WordsOccurence* wo = new WordsOccurence(DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Event),
//											DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Journal),
//											nullptr);
//	wo->process();
//	wo->deleteLater();

	QThread* searchThread = new QThread(this);
	WordsOccurence* wordFinder = new WordsOccurence(DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Event),
													DocumentsStorage::Instance().getDocumentsPath(CWTypes::DocumentType::Journal),
													nullptr);

	ui->tabWidget->setCurrentIndex(1);

	wordFinder->moveToThread(searchThread);

	connect(wordFinder, &WordsOccurence::progress, &m_pb, &ProgressBarWidget::setState);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, wordFinder, &WordsOccurence::process);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(wordFinder, &WordsOccurence::finished, searchThread, &QThread::quit);
	connect(wordFinder, &WordsOccurence::finished, wordFinder, &WordsOccurence::deleteLater);
	connect(wordFinder, &WordsOccurence::finished, &m_pb, &QWidget::hide);
	connect(wordFinder, &WordsOccurence::finished, ui->wordsOccurenceTableWidget, &QWidget::show);

	connect(&m_pb, &ProgressBarWidget::closed, wordFinder, &WordsOccurence::stop, Qt::ConnectionType::DirectConnection);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &SearchWordDialog::deleteLater);

	connect(wordFinder, &WordsOccurence::wordsFound, ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::setItems, Qt::ConnectionType::DirectConnection);

	m_pb.setWindowTitle("Идёт поиск...");
	m_pb.setParent(this);
	m_pb.setWindowFlags(Qt::Dialog);
	m_pb.setWindowModality(Qt::WindowModality::WindowModal);
	m_pb.show();
	searchThread->start();
}

void MainWindow::searchKeywords()
{
	QThread* searchThread = new QThread(this);
	KeywordsFinder* wordFinder = new KeywordsFinder(nullptr);

	ui->tabWidget->setCurrentIndex(1);
	ui->wordsOccurenceTableWidget->hide();

	wordFinder->moveToThread(searchThread);

	connect(wordFinder, &KeywordsFinder::reportState, &m_pb, &ProgressBarWidget::setState);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, wordFinder, &KeywordsFinder::process);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(wordFinder, &KeywordsFinder::finished, searchThread, &QThread::quit);
	connect(wordFinder, &KeywordsFinder::finished, wordFinder, &WordsOccurence::deleteLater);
	connect(wordFinder, &KeywordsFinder::finished, &m_pb, &QWidget::hide);

	connect(&m_pb, &ProgressBarWidget::closed, wordFinder, &KeywordsFinder::stop, Qt::ConnectionType::DirectConnection);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &SearchWordDialog::deleteLater);

	//connect(wordFinder, &WordsOccurence::wordsFound, ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::setItems, Qt::ConnectionType::DirectConnection);

	m_pb.setWindowTitle("Идёт поиск...");
	m_pb.setParent(this);
	m_pb.setWindowFlags(Qt::Dialog);
	m_pb.setWindowModality(Qt::WindowModality::WindowModal);
	m_pb.show();
	searchThread->start();
}

//void MainWindow::on_actionLoadEvent_triggered()
//{
//	loadNewEvent();
//}
