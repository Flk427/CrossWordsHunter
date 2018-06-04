#include "DocumentsStorageViewverWidget.h"
#include "ui_DocumentsStorageViewverWidget.h"
#include "core/ApplicationSettings.h"
#include <QDir>

DocumentsStorageViewverWidget::DocumentsStorageViewverWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DocumentsStorageViewverWidget)
{
	ui->setupUi(this);
	m_documentType = CWTypes::Event;
	connect(ui->documentViewer, &DocumentViewerWidget::searchSelectedWord, this, &DocumentsStorageViewverWidget::searchSelectedWord);
	connect(ui->listView, &QListView::doubleClicked, this, &DocumentsStorageViewverWidget::selectDocument);
	connect(this, &DocumentsStorageViewverWidget::resetText, ui->documentViewer, &DocumentViewerWidget::resetText);
}

DocumentsStorageViewverWidget::~DocumentsStorageViewverWidget()
{
	delete ui;
}

void DocumentsStorageViewverWidget::setDocumentType(const CWTypes::DocumentType& documentType)
{
	m_documentType = documentType;
}

void DocumentsStorageViewverWidget::setModel(QAbstractListModel* model)
{
	ui->listView->setModel(model);
}

void DocumentsStorageViewverWidget::selectFirstDocument()
{
	if (ui->listView->model()->rowCount() != 0)
	{
		selectDocument(ui->listView->model()->index(0, 0));
	}
}

void DocumentsStorageViewverWidget::selectDocument(QModelIndex index)
{
	QString documentName = ui->listView->model()->data(index, Qt::UserRole).toString();
	QString fileName = DocumentsStorage::Instance().getDocumentsPath(m_documentType) + QDir::separator() + documentName;

	ui->documentViewer->openDocument(fileName);
}

void DocumentsStorageViewverWidget::test()
{
	ui->documentViewer->test();
}
