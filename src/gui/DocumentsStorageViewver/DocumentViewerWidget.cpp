#include "DocumentViewerWidget.h"
#include "ui_DocumentViewerWidget.h"
#include <QToolButton>
#include <QTextEdit>
#include <QTextCodec>
#include "core/ApplicationSettings.h"

DocumentViewerWidget::DocumentViewerWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DocumentViewerWidget)
{
	ui->setupUi(this);

	connect(ui->documentEditor, &DocumentEditorWidget::searchSelectedWord, this, &DocumentViewerWidget::searchSelectedWord);
	connect(ui->toolButtonNextWord, &QToolButton::clicked, this, &DocumentViewerWidget::searchNextWord);
	connect(ui->toolButtonPrevWord, &QToolButton::clicked, this, &DocumentViewerWidget::searchPrevWord);
}

DocumentViewerWidget::~DocumentViewerWidget()
{
	delete ui;
}

void DocumentViewerWidget::openDocument(const QString& fileName)
{
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

void DocumentViewerWidget::searchWord(const QString& word, bool forward)
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

void DocumentViewerWidget::searchNextWord()
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
		ui->documentEditor->setFocus();
		searchWord(ApplicationSettings::Instance().getSearchWords().first());
		return;
//		search(ApplicationSettings::Instance().getSearchWords().first(), false);
	}
}

void DocumentViewerWidget::searchPrevWord()
{
	if (!ApplicationSettings::Instance().getSearchWords().empty())
	{
		ui->documentEditor->setFocus();
		searchWord(ApplicationSettings::Instance().getSearchWords().first(), false);
		return;
//		search(ApplicationSettings::Instance().getSearchWords().first(), false);
	}
}

void DocumentViewerWidget::test()
{
	QTextCursor textCursor = ui->documentEditor->textCursor();
	QTextBlockFormat textBlockFormat;
	textBlockFormat.setBackground(Qt::red);
	textCursor.select(QTextCursor::LineUnderCursor);
	textCursor.setBlockFormat(textBlockFormat);
	ui->documentEditor->setTextCursor(textCursor);
}

void DocumentViewerWidget::resetText()
{
	ui->documentEditor->clear();
}

void DocumentViewerWidget::search(const QString& str, bool matchCase)
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
