#include "DocumentsListModel.h"

#include <QBrush>

DocumentsListModel::DocumentsListModel()
{

}

void DocumentsListModel::setDocumentsList(const QStringList& stringList)
{
	m_stringList = stringList;
	dataChanged(createIndex(0, 0), createIndex(m_stringList.count() - 1, 0));
}

int DocumentsListModel::rowCount(const QModelIndex& parent) const
{
	return m_stringList.count();
}

QVariant DocumentsListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		return m_stringList.at(index.row());
	}
	else if (role == Qt::BackgroundRole)
	{
		// Выделить фон.
		if (index.row() % 2 == 0)
		{
			return QBrush(QColor::fromRgb(0xEE, 0xEE, 0xEE));
		}
	}

	return QVariant();
}
