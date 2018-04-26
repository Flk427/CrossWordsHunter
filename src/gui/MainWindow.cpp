#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TextEditorDialog.h"
#include "helpers/FilesHelpers.h"
#include "core/DocumentsStorage.h"
#include "core/ApplicationSettings.h"

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

//void MainWindow::on_actionLoadEvent_triggered()
//{
//	loadNewEvent();
//}
