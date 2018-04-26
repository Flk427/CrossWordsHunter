#include "DocumentEditorWidget.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "core/ApplicationSettings.h"

DocumentEditorWidget::DocumentEditorWidget(QWidget *parent) :
	QTextEdit(parent)
{
	setReadOnly(true);

	m_documentTextHighlighter = new DocumentTextHighlighter(this);

	setDocumentTextHighlighter(ApplicationSettings::Instance().getKeywords(), ApplicationSettings::Instance().getSearchWords());

	connect(&ApplicationSettings::Instance(), &ApplicationSettings::keywordsChanged, this, &DocumentEditorWidget::setDocumentTextHighlighter);

	createActions();
}

DocumentEditorWidget::~DocumentEditorWidget()
{
	foreach (QAction* action, m_actionMap)
	{
		delete action;
	}
}

void DocumentEditorWidget::addSelectedKeyword(bool)
{
	// ApplicationSettings выдаст сигнал обновления списка слов.

	if(textCursor().hasSelection())
	{
		ApplicationSettings::Instance().addKeyword(textCursor().selectedText());
	}
}

void DocumentEditorWidget::callSearchSelectedWord(bool)
{
	if(textCursor().hasSelection())
	{
		emit searchSelectedWord(textCursor().selectedText());
	}
}

void DocumentEditorWidget::setDocumentTextHighlighter(const QStringList& keywords, const QStringList& searchWords)
{
	m_documentTextHighlighter->setKeywords(keywords, DocumentTextHighlighter::htKeyword);
	m_documentTextHighlighter->setKeywords(searchWords, DocumentTextHighlighter::htSearch);
}

void DocumentEditorWidget::createActions()
{
	QAction* addKeywordAction = new QAction();
	connect(addKeywordAction, &QAction::triggered, this, &DocumentEditorWidget::addSelectedKeyword);
	m_actionMap["addKeyword"] = addKeywordAction;

	QAction* searchKeywordAction = new QAction();
	connect(searchKeywordAction, &QAction::triggered, this, &DocumentEditorWidget::callSearchSelectedWord);
	m_actionMap["searchWord"] = searchKeywordAction;
}

#ifndef QT_NO_CONTEXTMENU
void DocumentEditorWidget::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu *menu = createStandardContextMenu();

	QTextCursor cursor = textCursor();

	if(cursor.hasSelection())
	{
		m_actionMap["addKeyword"]->setText("Добавить ключевое слово: \"" + cursor.selectedText() + "\"");
		menu->insertAction(menu->actions().at(0), m_actionMap["addKeyword"]);

		m_actionMap["searchWord"]->setText("Искать фрагмент текста: \"" + cursor.selectedText() + "\"");
		menu->insertAction(menu->actions().at(1), m_actionMap["searchWord"]);

		menu->insertSeparator(menu->actions().at(2));
	}

	menu->exec(event->globalPos());
	delete menu;
}
#endif // QT_NO_CONTEXTMENU
