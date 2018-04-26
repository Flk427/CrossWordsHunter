#ifndef DOCUMENTEDITORWIDGET_H
#define DOCUMENTEDITORWIDGET_H

#include <QTextEdit>
#include <QMap>
#include <QAction>
#include "core/DocumentTextHighlighter.h"
#include "../core/DocumentsStorage.h"

class DocumentEditorWidget : public QTextEdit
{
	Q_OBJECT

public:
	explicit DocumentEditorWidget(QWidget *parent = 0);
	~DocumentEditorWidget();

signals:
	void searchSelectedWord(const QString& word);

private slots:
	void addSelectedKeyword(bool toggled);
	void callSearchSelectedWord(bool toggled);
	void setDocumentTextHighlighter(const QStringList& keywords, const QStringList& searchWords);

private:
	QMap<QString, QAction*> m_actionMap;
	DocumentTextHighlighter* m_documentTextHighlighter;

	void createActions();

	// QWidget interface
protected:
	virtual void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // DOCUMENTEDITORWIDGET_H
