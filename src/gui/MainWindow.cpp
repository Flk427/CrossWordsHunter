#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TextEditorDialog.h"
#include "helpers/FilesHelpers.h"
#include "core/DocumentsStorage.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->eventsViewverWidget->setDocumentType(DocumentsStorage::Event);
	ui->journalsViewverWidget->setDocumentType(DocumentsStorage::Journal);

	ui->eventsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(DocumentsStorage::Event));
	ui->journalsViewverWidget->setModel(DocumentsStorage::Instance().getDocumentsListModel(DocumentsStorage::Journal));

	connect(&DocumentsStorage::Instance(), &DocumentsStorage::storageUpdatedNotice, this, &MainWindow::statusUpdate);

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
		DocumentsStorage::Instance().addDocument(DocumentsStorage::DocumentType::Event, editor.getTextDocument());
	}
}

void MainWindow::loadNewJournal()
{
	TextEditorDialog editor;

	if (editor.exec() == QDialog::Accepted)
	{
		// acceptJournal
		DocumentsStorage::Instance().addDocument(DocumentsStorage::DocumentType::Journal, editor.getTextDocument());
	}
}

void MainWindow::statusUpdate(QString text)
{
	statusBar()->showMessage(text);
}

void MainWindow::eventsVisible(bool visible)
{
	ui->eventsViewverWidget->setVisible(visible);
}

void MainWindow::journalsVisible(bool visible)
{
	ui->journalsViewverWidget->setVisible(visible);
}
