#ifndef DOCUMENTSSTORAGEVIEWVERWIDGET_H
#define DOCUMENTSSTORAGEVIEWVERWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "../core/DocumentsStorage.h"

namespace Ui {
class DocumentsStorageViewverWidget;
}

class DocumentsStorageViewverWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DocumentsStorageViewverWidget(QWidget *parent = nullptr);
	~DocumentsStorageViewverWidget();

	void setDocumentType(const CWTypes::DocumentType& documentType);

signals:
	void searchSelectedWord(const QString& word);

private:
	Ui::DocumentsStorageViewverWidget *ui;

	CWTypes::DocumentType m_documentType;

	void search(const QString& str, bool matchCase);
	void searchWord(const QString& word, bool forward = true);

public slots:
	void setModel(QAbstractListModel* model);
	void selectFirstDocument();
	void selectDocument(QModelIndex index);
	void test();
	void resetText();
	void searchNextWord();
	void searchPrevWord();
};

#endif // DOCUMENTSSTORAGEVIEWVERWIDGET_H
