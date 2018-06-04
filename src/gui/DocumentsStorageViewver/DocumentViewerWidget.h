#ifndef DOCUMENTVIEWERWIDGET_H
#define DOCUMENTVIEWERWIDGET_H

#include <QWidget>

namespace Ui {
class DocumentViewerWidget;
}

class DocumentViewerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DocumentViewerWidget(QWidget *parent = 0);
	~DocumentViewerWidget();

	void openDocument(const QString& fileName);

	void test();

signals:
	void searchSelectedWord(const QString& word);

public slots:
	void resetText();

private:
	Ui::DocumentViewerWidget *ui;

	void search(const QString& str, bool matchCase);
	void searchWord(const QString& word, bool forward = true);

private slots:
	void searchNextWord();
	void searchPrevWord();

};

#endif // DOCUMENTVIEWERWIDGET_H
