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
	connect(ui->textEdit, &DocumentEditorWidget::searchSelectedWord, this, &DocumentsStorageViewverWidget::searchSelectedWord);
	connect(ui->listView, &QListView::doubleClicked, this, &DocumentsStorageViewverWidget::documentSelected);

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

void DocumentsStorageViewverWidget::documentSelected(QModelIndex index)
{
	QString documentName = ui->listView->model()->data(index, Qt::DisplayRole).toString();
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
			ui->textEdit->setHtml(str);
		}
		else
		{
			str = QString::fromLocal8Bit(data);
			ui->textEdit->setPlainText(str);
		}

		searchNextWord();
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

void DocumentsStorageViewverWidget::resetText()
{
	ui->textEdit->clear();
}

void DocumentsStorageViewverWidget::searchNextWord()
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
		ui->textEdit->setFocus();
		searchWord(ApplicationSettings::Instance().getSearchWords().first());
		return;
//		search(ApplicationSettings::Instance().getSearchWords().first(), false);
	}
}

void DocumentsStorageViewverWidget::searchPrevWord()
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
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
		ui->textEdit->moveCursor(QTextCursor::Start);
		QColor color = QColor(Qt::gray).lighter(130);

		while(ui->textEdit->find(str))
		{
			QTextEdit::ExtraSelection extra;
			extra.format.setBackground(color);

			extra.cursor = ui->textEdit->textCursor();
			extraSelections.append(extra);
		}
	}

	ui->textEdit->setExtraSelections(extraSelections);
}

void DocumentsStorageViewverWidget::searchWord(const QString& word, bool forward)
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
		QTextDocument::FindFlags flag;

		if (!forward) flag |= QTextDocument::FindBackward;
		// if (casesens) flag |= QTextDocument::FindCaseSensitively;
		// if (words) flag |= QTextDocument::FindWholeWords;

		QTextCursor cursor = ui->textEdit->textCursor();
		// here , you save the cursor position
		//QTextCursor cursorSaved = cursor;

		if (!ui->textEdit->find(word, flag))
		{
			cursor.movePosition(forward ? QTextCursor::End : QTextCursor::Start);
		}

//		search(ApplicationSettings::Instance().getSearchWords().first(), false);
	}
}
