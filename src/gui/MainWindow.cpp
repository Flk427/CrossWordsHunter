#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TextEditorDialog.h"
#include "helpers/FilesHelpers.h"
#include "core/DocumentsStorage.h"
#include "core/ApplicationSettings.h"
#include "core/WordsOccurence.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	setWindowIcon(QIcon(":/img/CrossWordsHunter.ico"));

	m_searchWordDialog = new SearchWordDialog(this);

	ui->setupUi(this);

	ui->eventsViewverWidget->setDocumentType(CWTypes::Event);
	ui->journalsViewverWidget->setDocumentType(CWTypes::Journal);

	ui->eventsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(CWTypes::Event));
	ui->journalsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(CWTypes::Journal));

	connect(&DocumentsStorage::Instance(), &DocumentsStorage::storageUpdatedNotice, this, &MainWindow::updateStatus);
	connect(ui->eventsViewverWidget, &DocumentsStorageViewverWidget::searchSelectedWord, this, &MainWindow::showSearchWordForm);
	connect(ui->journalsViewverWidget, &DocumentsStorageViewverWidget::searchSelectedWord, this, &MainWindow::showSearchWordForm);
	connect(ui->action_3, &QAction::triggered, this, &MainWindow::searchReset);
	connect(ui->action, &QAction::triggered, this, &MainWindow::test);

	DocumentsStorage::Instance().updateDocumentsLists();
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
		if (m_searchWordDialog->exec(ApplicationSettings::Instance().getKeywords()) == QDialog::Accepted)
		{
			resetDocuments();
			ui->tabWidget->setCurrentIndex(1);
		}
	}
	else
	{
		resetDocuments();
		m_searchWordDialog->startSearchWord(word);
	}
}

void MainWindow::searchReset()
{
	resetDocuments();
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

void MainWindow::test()
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

	wordFinder->moveToThread(searchThread);

	connect(wordFinder, &WordsOccurence::progress, &m_pb, &ProgressBarWidget::setState);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, wordFinder, &WordsOccurence::process);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(wordFinder, &WordsOccurence::finished, searchThread, &QThread::quit);
	connect(wordFinder, &WordsOccurence::finished, wordFinder, &WordsOccurence::deleteLater);
	connect(wordFinder, &WordsOccurence::finished, &m_pb, &QWidget::hide);

	connect(&m_pb, &ProgressBarWidget::closed, wordFinder, &WordsOccurence::stop, Qt::ConnectionType::DirectConnection);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &SearchWordDialog::deleteLater);

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
