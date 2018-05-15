#include "KeywordsListModel.h"
#include "core/ApplicationSettings.h"

KeywordsListModel::KeywordsListModel(QObject *parent) : QAbstractListModel(parent)
{
	readKeywords();
}

KeywordsListModel::~KeywordsListModel()
{

}

int KeywordsListModel::rowCount(const QModelIndex&) const
{
	return m_keywords.count();
}

QVariant KeywordsListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (index.row() >= m_keywords.count())
		{
			return QVariant();
		}

		return m_keywords.at(index.row());
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

void KeywordsListModel::readKeywords()
{
	m_keywords = ApplicationSettings::Instance().readKeywords();

	// TODO: Что-то делать, если список пустой.
	if (!m_keywords.empty())
	{
		dataChanged(createIndex(0, 0), createIndex(m_keywords.count() - 1, 0));
	}

	emit keywordsListChanged(m_keywords);
}

KeywordsListModel& KeywordsListModel::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static KeywordsListModel m;
	return m;
}

QStringList KeywordsListModel::keywords() const
{
	return m_keywords;
}

void KeywordsListModel::addKeyword(const QString& keyword)
{
	if (!keyword.isEmpty() && !m_keywords.contains(keyword, Qt::CaseInsensitive))
	{
		m_keywords.push_back(keyword);
		ApplicationSettings::Instance().addKeyword(keyword);
		emit keywordsListChanged(m_keywords);
	}
}
