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

	connect(&DocumentsStorage::Instance(), &DocumentsStorage::storageUpdated, this, &MainWindow::statusUpdate);
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
		DocumentsStorage::Instance().addDocument(DocumentsStorage::DocumentType::Event, this, editor.getTextDocument());
	}
}

void MainWindow::loadNewJournal()
{
	TextEditorDialog editor;

	if (editor.exec() == QDialog::Accepted)
	{
		// acceptJournal
		DocumentsStorage::Instance().addDocument(DocumentsStorage::DocumentType::Journal, this, editor.getTextDocument());
	}
}

void MainWindow::statusUpdate(QString text)
{
	statusBar()->showMessage(text);
}
