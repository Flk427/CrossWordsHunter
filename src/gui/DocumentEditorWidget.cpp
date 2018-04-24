#include "DocumentEditorWidget.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "core/ApplicationSettings.h"

DocumentEditorWidget::DocumentEditorWidget(QWidget *parent) :
	QTextEdit(parent)
{
	setReadOnly(true);

	m_documentTextHighlighter = new DocumentTextHighlighter(this);

	setDocumentTextHighlighter(ApplicationSettings::Instance().getKeywords());

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

void DocumentEditorWidget::setDocumentTextHighlighter(const QStringList& keywords)
{
	m_documentTextHighlighter->setKeywords(keywords);
}

void DocumentEditorWidget::createActions()
{
	QAction* addKeywordAction = new QAction();

	//addKeywordAction->setText("Add keyword");
	connect(addKeywordAction, &QAction::triggered, this, &DocumentEditorWidget::addSelectedKeyword);

	m_actionMap["addKeyword"] = addKeywordAction;
}

#ifndef QT_NO_CONTEXTMENU
void DocumentEditorWidget::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu *menu = createStandardContextMenu();

	QTextCursor cursor = textCursor();

	if(cursor.hasSelection())
	{
		m_actionMap["addKeyword"]->setText("Add keyword: \"" + cursor.selectedText() + "\"");
		menu->insertAction(menu->actions().at(0), m_actionMap["addKeyword"]);
		menu->insertSeparator(menu->actions().at(1));
	}

	menu->exec(event->globalPos());
	delete menu;
}
#endif // QT_NO_CONTEXTMENU
