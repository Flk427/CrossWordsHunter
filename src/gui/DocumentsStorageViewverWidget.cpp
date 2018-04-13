#include "DocumentsStorageViewverWidget.h"
#include "ui_DocumentsStorageViewverWidget.h"

#include <QDir>
#include <QTextEdit>

DocumentsStorageViewverWidget::DocumentsStorageViewverWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DocumentsStorageViewverWidget)
{
	ui->setupUi(this);

	m_documentType = DocumentsStorage::Event;
	m_documentTextHighlighter = new DocumentTextHighlighter(ui->textEdit);

//	connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &DocumentsStorageViewverWidget::test);
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

void DocumentsStorageViewverWidget::test()
{
	QTextCursor textCursor = ui->textEdit->textCursor();
	QTextBlockFormat textBlockFormat;
	textBlockFormat.setBackground(Qt::red);
	textCursor.select(QTextCursor::LineUnderCursor);
	textCursor.setBlockFormat(textBlockFormat);
	ui->textEdit->setTextCursor(textCursor);
}
