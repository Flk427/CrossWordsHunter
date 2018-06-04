#include "DocumentViewerWidget.h"
#include "ui_DocumentViewerWidget.h"
#include <QToolButton>
#include <QTextEdit>
#include <QTextCodec>
#include <QDebug>
#include "core/ApplicationSettings.h"

DocumentViewerWidget::DocumentViewerWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DocumentViewerWidget),
	m_currentSelectedWord(0)
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

		fillWordsIndex();
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

		if (!ui->documentEditor->find(word, flag))
		{
			//cursor.movePosition(forward ? QTextCursor::End : QTextCursor::Start);
		}
	}
}

void DocumentViewerWidget::searchNextWord()
{
	if (m_currentSelectedWord + 1 < m_wordsIndex.size() && !m_wordsIndex.empty())
	{
		m_currentSelectedWord++;
	}

	updateSelection();
}

void DocumentViewerWidget::searchPrevWord()
{
	if (m_currentSelectedWord > 0 && !m_wordsIndex.empty())
	{
		m_currentSelectedWord--;
	}

	updateSelection();
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
	m_wordsIndex.clear();
	m_currentSelectedWord = 0;
}

void DocumentViewerWidget::fillWordsIndex()
{
	m_wordsIndex.clear();
	m_currentSelectedWord = 0;

	findWords(ApplicationSettings::Instance().getSearchWords());
	findWords(ApplicationSettings::Instance().readKeywords());

	if (m_wordsIndex.size() > 0)
	{
		qSort(m_wordsIndex.begin(), m_wordsIndex.end(),
			  [](WordAttributes a, WordAttributes b)
		{
			return (a.anchor < b.anchor);
		});

		updateSelection();
	}
}

void DocumentViewerWidget::findWords(const QStringList wordsList)
{
	foreach (const QString& word, wordsList)
	{
		// qDebug() << word;
		QTextCursor cursor = ui->documentEditor->textCursor();

		cursor.movePosition(QTextCursor::Start);

		bool finished;

		do
		{
			finished = !ui->documentEditor->find(word, QTextDocument::FindFlag());

			if (!finished)
			{
				qDebug() << word << ui->documentEditor->textCursor().anchor() << ui->documentEditor->textCursor().position();

				WordAttributes wordAttributes;
				wordAttributes.anchor = ui->documentEditor->textCursor().anchor();
				wordAttributes.position = ui->documentEditor->textCursor().position();
				m_wordsIndex.push_back(wordAttributes);
			}
		}
		while (!finished);
	}
}

void DocumentViewerWidget::updateSelection()
{
	if (!m_wordsIndex.empty() && m_currentSelectedWord < m_wordsIndex.size() && m_currentSelectedWord >= 0)
	{
		QTextCursor cursor = ui->documentEditor->textCursor();
		cursor.setPosition(m_wordsIndex.at(m_currentSelectedWord).anchor, QTextCursor::MoveMode::MoveAnchor);
		cursor.setPosition(m_wordsIndex.at(m_currentSelectedWord).position, QTextCursor::MoveMode::KeepAnchor);
		ui->documentEditor->setTextCursor(cursor);
		ui->documentEditor->setFocus();
	}
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
