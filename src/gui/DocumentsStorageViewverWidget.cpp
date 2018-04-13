#include "DocumentsStorageViewverWidget.h"
#include "ui_DocumentsStorageViewverWidget.h"

#include <QDir>

DocumentsStorageViewverWidget::DocumentsStorageViewverWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DocumentsStorageViewverWidget)
{
	ui->setupUi(this);

	m_documentType = DocumentsStorage::Event;
}

DocumentsStorageViewverWidget::~DocumentsStorageViewverWidget()
{
	delete ui;
}

void DocumentsStorageViewverWidget::setDocumentType(const DocumentsStorage::DocumentType& documentType)
{
	m_documentType = documentType;
}

void DocumentsStorageViewverWidget::setModel(QAbstractListModel* model)
{
	ui->listView->setModel(model);
}

void DocumentsStorageViewverWidget::documentSelected(QModelIndex index)
{
	QString documentName = ui->listView->model()->data(index, Qt::DisplayRole).toString();
	QString fileName = DocumentsStorage::Instance().getDocumentsPath(m_documentType) + QDir::separator() + documentName;
	QFile f(fileName);

	if (f.open(QFile::ReadOnly))
	{
		QString html = QString(f.readAll());
		ui->textEdit->setHtml(html);
		f.close();
	}
}
