#ifndef DOCUMENTSSTORAGEVIEWVERWIDGET_H
#define DOCUMENTSSTORAGEVIEWVERWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "../../core/DocumentsStorage.h"

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
	void resetText();

private:
	Ui::DocumentsStorageViewverWidget *ui;

	CWTypes::DocumentType m_documentType;

public slots:
	void setModel(QAbstractListModel* model);
	void selectFirstDocument();
	void selectDocument(QModelIndex index);
	void test();
};

#endif // DOCUMENTSSTORAGEVIEWVERWIDGET_H
