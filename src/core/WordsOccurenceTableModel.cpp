#include "WordsOccurenceTableModel.h"
#include <QColor>
#include <QBrush>

WordsOccurenceTableModel::WordsOccurenceTableModel(QObject* parent) :
	QAbstractTableModel(parent)
{
}

QString WordsOccurenceTableModel::getWord(QModelIndex index)
{
	if (index.row() < m_wordsOccuring.count())
	{
		return m_wordsOccuring[index.row()].word;
	}
	else
	{
		return QString() ;
	}
}

WordsOccurenceTableModel::WordInfo WordsOccurenceTableModel::getWordInfo(int row)
{
	if (row < m_wordsOccuring.count())
	{
		return m_wordsOccuring[row];
	}
	else
	{
		return WordInfo();
	}
}

void WordsOccurenceTableModel::setItems(const CWTypes::WordsOccuring* wordsOccuring)
{
	beginResetModel();
	m_wordsOccuring.clear();
	endResetModel();

	foreach (const QString& word, wordsOccuring->keys())
	{
		WordInfo wordInfo;

		if (wordsOccuring->value(word).firstOccuring
			&& wordsOccuring->value(word).secondOccuring
			&& wordsOccuring->value(word).firstOccuring < 2
			&& wordsOccuring->value(word).secondOccuring < 2)
		{
			wordInfo.word = word;
			wordInfo.occuring = wordsOccuring->value(word);
			m_wordsOccuring.append(wordInfo);
		}
	}

//	qSort(m_wordsOccuring.begin(), m_wordsOccuring.end(),
//			  [](WordInfo a, WordInfo b)
//	{
//		return (a.occuring.firstOccuring + a.occuring.secondOccuring) < (b.occuring.firstOccuring + b.occuring.secondOccuring);
//	});

	if (!m_wordsOccuring.empty())
	{
		insertRows(0, m_wordsOccuring.count() - 1, QModelIndex());
		dataChanged(index(0, 0), index(m_wordsOccuring.count() - 1, 2));
	}

	layoutChanged();
}


int WordsOccurenceTableModel::rowCount(const QModelIndex&) const
{
	return m_wordsOccuring.count();
}

int WordsOccurenceTableModel::columnCount(const QModelIndex&) const
{
	return 3;
}

QVariant WordsOccurenceTableModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (index.row() >= m_wordsOccuring.count())
		{
			return QVariant();
		}

		switch (index.column())
		{
			case 0:
				return m_wordsOccuring[index.row()].word;
			case 1:
				return m_wordsOccuring[index.row()].occuring.firstOccuring;
			case 2:
				return m_wordsOccuring[index.row()].occuring.secondOccuring;
			default:
				return QVariant();
		}
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


bool WordsOccurenceTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	beginInsertRows(parent, 0, count);
	endInsertRows();
	return true;
}

bool WordsOccurenceTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	beginRemoveRows(parent, 0, m_wordsOccuring.count());
	endRemoveRows();
	return true;
}


QVariant WordsOccurenceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Orientation::Horizontal)
		{
			switch (section)
			{
				case 0: return "Слово";
				case 1: return "В сводках";
				case 2: return "В реестрах";
			}
		}

		if (orientation == Qt::Orientation::Vertical && section <= m_wordsOccuring.size())
		{
			return section + 1;
		}
	}

	return QVariant();
}
