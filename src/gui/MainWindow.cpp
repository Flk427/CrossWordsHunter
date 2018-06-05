#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TextEditorDialog.h"
#include "core/DocumentsStorage.h"
#include "core/ApplicationSettings.h"
#include "core/KeywordsListModel.h"
#include "search/SearchConjunction.h"
#include "search/SearchKeywords.h"
#include "search/SearchWord.h"
#include "document_import/ImportDocuments.h"
#include "tests/tests.h"

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

	ui->eventsViewverWidget->setDocumentType(CWTypes::Event); // setDataStorage
	ui->journalsViewverWidget->setDocumentType(CWTypes::Journal);

	ui->eventsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(CWTypes::Event));
	ui->journalsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(CWTypes::Journal));

	connect(ui->toolButton_3, &QToolButton::toggled, ui->eventsViewverWidget, &DocumentsStorageViewverWidget::setVisible);
	connect(ui->toolButton_4, &QToolButton::toggled, ui->journalsViewverWidget, &DocumentsStorageViewverWidget::setVisible);

	connect(&DocumentsStorage::Instance(), &DocumentsStorage::storageUpdatedNotice, this, &MainWindow::updateStatus);
	connect(ui->eventsViewverWidget, &DocumentsStorageViewverWidget::searchSelectedWord, this, &MainWindow::searchWord);
	connect(ui->journalsViewverWidget, &DocumentsStorageViewverWidget::searchSelectedWord, this, &MainWindow::searchWord);
	//connect(ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::searchSelectedWord, this, &MainWindow::showSearchWordForm);
	connect(ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::wordSelectionChanged, this, &MainWindow::resetDocuments);
	connect(ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::wordSelectionChanged, ui->eventsViewverWidget, &DocumentsStorageViewverWidget::selectFirstDocument);
	connect(ui->wordsOccurenceTableWidget, &WordsOccurenceTableWidget::wordSelectionChanged, ui->journalsViewverWidget, &DocumentsStorageViewverWidget::selectFirstDocument);

	connect(ui->actionSearchReset, &QAction::triggered, this, &MainWindow::searchReset);
	//connect(ui->actionShowSearchWordForm, &QAction::triggered, this, &MainWindow::searchWord); // соединил в дизайнере, т.к. типы разные.
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

void MainWindow::searchWord(const QString& word)
{
	if (word.isEmpty())
	{
		if (m_searchWordDialog->exec(KeywordsListModel::Instance().keywords()) == QDialog::Accepted)
		{
			ui->wordsOccurenceTableWidget->hide();
			resetDocuments();
			ui->tabWidget->setCurrentIndex(0);

			SearchWord* searchWord = new SearchWord();
			searchWord->start(this, m_searchWordDialog->getWord());
		}
	}
	else
	{
		ui->wordsOccurenceTableWidget->hide();
		resetDocuments();
		SearchWord* searchWord = new SearchWord();
		searchWord->start(this, word);
	}
}

void MainWindow::searchReset()
{
	ui->wordsOccurenceTableWidget->hide();
	DocumentsStorage::Instance().readDocumentsLists();
	ApplicationSettings::Instance().setSearchWord("");
}

void MainWindow::resetDocuments()
{
	ui->eventsViewverWidget->resetText();
	ui->journalsViewverWidget->resetText();
}

void MainWindow::setupOccurenceTable(const CWTypes::WordsOccuring* wordsOccuring)
{
	ui->wordsOccurenceTableWidget->setItems(wordsOccuring);
}

void MainWindow::showOccurenceTable()
{
	ui->wordsOccurenceTableWidget->show();
}

void MainWindow::on_actionQuit_triggered()
{
	// Эта штука автоматически связывается через QMetaObject::connectSlotsByName(MainWindow);
	close();
}

void MainWindow::searchConjunction()
{
	ui->tabWidget->setCurrentIndex(0);
	resetDocuments();

	DocumentsStorage::Instance().setDocumentsList(CWTypes::DocumentType::Event, QStringList());
	DocumentsStorage::Instance().setDocumentsList(CWTypes::DocumentType::Journal, QStringList());

	SearchConjunction* searchConjunction = new SearchConjunction();
	searchConjunction->start(this);
}

void MainWindow::searchKeywords()
{
	ui->tabWidget->setCurrentIndex(0);
	ui->wordsOccurenceTableWidget->hide();
	resetDocuments();

	SearchKeywords* searchKeywords = new SearchKeywords();
	searchKeywords->start(this);
}

//void MainWindow::on_actionLoadEvent_triggered()
//{
//	loadNewEvent();
//}

void MainWindow::on_actiontest_qax_triggered()
{
	t::testQAX(this);
}

void MainWindow::on_actiontest_mime_triggered()
{
	t::testMime();
}

void MainWindow::on_actiontest_Excel_1_triggered()
{
	t::testExcel1();
}

void MainWindow::on_actiontest_Libre_Office_triggered()
{
	t::testLibreOffice(this);
}

void MainWindow::on_actionImportEventsOO_triggered()
{
	ui->tabWidget->setCurrentIndex(0);
	ui->wordsOccurenceTableWidget->hide();
	resetDocuments();

	ImportDocuments* importOpenOfficeDocuments = new ImportDocuments();
	importOpenOfficeDocuments->start(this, CWTypes::OfficeType::OpenOffice, CWTypes::DocumentType::Event);
}

void MainWindow::on_actionImportJournalsOO_triggered()
{
	ui->tabWidget->setCurrentIndex(0);
	ui->wordsOccurenceTableWidget->hide();
	resetDocuments();

	ImportDocuments* importOpenOfficeDocuments = new ImportDocuments();
	importOpenOfficeDocuments->start(this, CWTypes::OfficeType::OpenOffice, CWTypes::DocumentType::Journal);
}

void MainWindow::on_actionImportEventsMSO_triggered()
{
	ui->tabWidget->setCurrentIndex(0);
	ui->wordsOccurenceTableWidget->hide();
	resetDocuments();

	ImportDocuments* importOpenOfficeDocuments = new ImportDocuments();
	importOpenOfficeDocuments->start(this, CWTypes::OfficeType::MicrosoftOffice, CWTypes::DocumentType::Event);
}

void MainWindow::on_actionImportJournalsMSO_triggered()
{
	ui->tabWidget->setCurrentIndex(0);
	ui->wordsOccurenceTableWidget->hide();
	resetDocuments();

	ImportDocuments* importOpenOfficeDocuments = new ImportDocuments();
	importOpenOfficeDocuments->start(this, CWTypes::OfficeType::MicrosoftOffice, CWTypes::DocumentType::Journal);
}

void MainWindow::on_actiontest_threads_triggered()
{
	t::threadTest();
}
