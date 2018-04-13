#ifndef DOCUMENTSLISTMODEL_H
#define DOCUMENTSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class DocumentsListModel : public QAbstractListModel
{
	Q_OBJECT
public:
	DocumentsListModel();

	void setDocumentsList(const QStringList& stringList);

	// QAbstractItemModel interface
public:
	virtual int rowCount(const QModelIndex& parent) const override;
	virtual QVariant data(const QModelIndex& index, int role) const override;

private:
	QStringList m_stringList;
};

#endif // DOCUMENTSLISTMODEL_H
