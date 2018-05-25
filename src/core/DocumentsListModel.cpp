#include "DocumentsListModel.h"

#include <QBrush>
#include <QFileInfo>

DocumentsListModel::DocumentsListModel()
{

}

void DocumentsListModel::setDocumentsList(const QStringList& stringList)
{
	m_stringList = stringList;
	dataChanged(createIndex(0, 0), createIndex(m_stringList.count() - 1, 0));
}

int DocumentsListModel::rowCount(const QModelIndex&) const
{
	return m_stringList.count();
}

QVariant DocumentsListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		// Вернёт имя файла, без расширения ".html".
		if (index.row() >= m_stringList.count())
		{
			return QVariant();
		}

		QString fileName = m_stringList.at(index.row());

		return QFileInfo(fileName).completeBaseName();
	}
	else if (role == Qt::UserRole)
	{
		// Вернёт полное имя файла.
		if (index.row() >= m_stringList.count())
		{
			return QVariant();
		}

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
