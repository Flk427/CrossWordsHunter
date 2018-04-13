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
	explicit DocumentsStorageViewverWidget(QWidget *parent = 0);
	~DocumentsStorageViewverWidget();

	void setDocumentType(const DocumentsStorage::DocumentType& documentType);

private:
	Ui::DocumentsStorageViewverWidget *ui;

	DocumentsStorage::DocumentType m_documentType;

public slots:
	void setModel(QAbstractListModel* model);
	void documentSelected(QModelIndex index);
};

#endif // DOCUMENTSSTORAGEVIEWVERWIDGET_H
