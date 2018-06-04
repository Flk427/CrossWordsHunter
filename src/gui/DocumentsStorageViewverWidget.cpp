#include "DocumentsStorageViewverWidget.h"
#include "ui_DocumentsStorageViewverWidget.h"

#include <QDir>
#include <QTextEdit>
#include <QTextCodec>

#include "core/ApplicationSettings.h"

DocumentsStorageViewverWidget::DocumentsStorageViewverWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DocumentsStorageViewverWidget)
{
	ui->setupUi(this);

	m_documentType = CWTypes::Event;
	connect(ui->documentEditor, &DocumentEditorWidget::searchSelectedWord, this, &DocumentsStorageViewverWidget::searchSelectedWord);
	connect(ui->listView, &QListView::doubleClicked, this, &DocumentsStorageViewverWidget::selectDocument);

	connect(ui->toolButtonNextWord, &QToolButton::clicked, this, &DocumentsStorageViewverWidget::searchNextWord);
	connect(ui->toolButtonPrevWord, &QToolButton::clicked, this, &DocumentsStorageViewverWidget::searchPrevWord);

//	connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &DocumentsStorageViewverWidget::test);
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
	QFile f(fileName);

	if (f.open(QFile::ReadOnly))
	{
		QByteArray data = f.readAll();
		f.close();

		QTextCodec *codec = Qt::codecForHtml(data);
		QString str = codec->toUnicode(data);

		if (Qt::mightBeRichText(str))
		{
			ui->documentEditor->setHtml(str);
		}
		else
		{
			str = QString::fromLocal8Bit(data);
			ui->documentEditor->setPlainText(str);
		}

		searchNextWord();
	}
}

void DocumentsStorageViewverWidget::test()
{
	QTextCursor textCursor = ui->documentEditor->textCursor();
	QTextBlockFormat textBlockFormat;
	textBlockFormat.setBackground(Qt::red);
	textCursor.select(QTextCursor::LineUnderCursor);
	textCursor.setBlockFormat(textBlockFormat);
	ui->documentEditor->setTextCursor(textCursor);
}

void DocumentsStorageViewverWidget::resetText()
{
	ui->documentEditor->clear();
}

void DocumentsStorageViewverWidget::searchNextWord()
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
		ui->documentEditor->setFocus();
		searchWord(ApplicationSettings::Instance().getSearchWords().first());
		return;
//		search(ApplicationSettings::Instance().getSearchWords().first(), false);
	}
}

void DocumentsStorageViewverWidget::searchPrevWord()
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
		ui->documentEditor->setFocus();
		searchWord(ApplicationSettings::Instance().getSearchWords().first(), false);
		return;
//		search(ApplicationSettings::Instance().getSearchWords().first(), false);
	}
}

void DocumentsStorageViewverWidget::search(const QString& str, bool matchCase)
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	//if(!ui->textEdit->isReadOnly())
	{
		ui->documentEditor->moveCursor(QTextCursor::Start);
		QColor color = QColor(Qt::gray).lighter(130);

		while(ui->documentEditor->find(str))
		{
			QTextEdit::ExtraSelection extra;
			extra.format.setBackground(color);

			extra.cursor = ui->documentEditor->textCursor();
			extraSelections.append(extra);
		}
	}

	ui->documentEditor->setExtraSelections(extraSelections);
}

void DocumentsStorageViewverWidget::searchWord(const QString& word, bool forward)
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
		QTextDocument::FindFlags flag;

		if (!forward) flag |= QTextDocument::FindBackward;
		// if (casesens) flag |= QTextDocument::FindCaseSensitively;
		// if (words) flag |= QTextDocument::FindWholeWords;

		QTextCursor cursor = ui->documentEditor->textCursor();
		// here , you save the cursor position
		//QTextCursor cursorSaved = cursor;

		if (!ui->documentEditor->find(word, flag))
		{
			cursor.movePosition(forward ? QTextCursor::End : QTextCursor::Start);
		}

//		search(ApplicationSettings::Instance().getSearchWords().first(), false);
	}
}
