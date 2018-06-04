#ifndef DOCUMENTVIEWERWIDGET_H
#define DOCUMENTVIEWERWIDGET_H

#include <QWidget>

namespace Ui {
class DocumentViewerWidget;
}

/*!
\brief The DocumentViewerWidget class

Для перехода по найденным словам составляется список слов и их позиций,
упорядоченный по возрастанию позиции.
*/
class DocumentViewerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DocumentViewerWidget(QWidget *parent = nullptr);
	~DocumentViewerWidget();

	void openDocument(const QString& fileName);

	void test();

signals:
	void searchSelectedWord(const QString& word);

public slots:
	void resetText();

private:
	typedef struct
	{
		int anchor;
		int position;
	} WordAttributes;

	typedef QList<WordAttributes> WordsIndex;

	Ui::DocumentViewerWidget *ui;
	WordsIndex m_wordsIndex;
	int m_currentSelectedWord;

	void fillWordsIndex();
	void findWords(const QStringList wordsList);
	void updateSelection();
	void search(const QString& str, bool matchCase); // не исп.
	void searchWord(const QString& word, bool forward = true); // не исп.

private slots:
	void searchNextWord();
	void searchPrevWord();

};

#endif // DOCUMENTVIEWERWIDGET_H
