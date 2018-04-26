#include "ApplicationSettings.h"

ApplicationSettings::ApplicationSettings()
{
	m_settings = new QSettings("config.ini", QSettings::IniFormat);
	readKeywords();
}

ApplicationSettings::~ApplicationSettings()
{
	delete m_settings;
}

void ApplicationSettings::readKeywords()
{
	m_keywords.clear();

	m_settings->beginGroup("keywords");
	const QStringList childKeys = m_settings->childKeys();

	foreach (const QString &childKey, childKeys)
	{
		m_keywords << childKey;
	}

	m_settings->endGroup();
}

void ApplicationSettings::addKeyword(const QString& keyword)
{
	if (!keyword.isEmpty() && !m_keywords.contains(keyword, Qt::CaseInsensitive))
	{
		m_settings->beginGroup("keywords");
		m_settings->setValue(keyword, "");
		m_settings->endGroup();

		m_keywords.push_back(keyword);
		emit keywordsChanged(m_keywords, m_searchWords);
	}
}

void ApplicationSettings::setSearchWord(const QString& searchWord)
{
	if (!searchWord.isEmpty())
	{
		if (!m_keywords.contains(searchWord, Qt::CaseInsensitive))
		{
			m_searchWords.clear();
			m_searchWords.push_back(searchWord);
			emit keywordsChanged(m_keywords, m_searchWords);
		}
	}
	else
	{
		m_searchWords.clear();
		emit keywordsChanged(m_keywords, m_searchWords);
	}
}

ApplicationSettings& ApplicationSettings::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static ApplicationSettings s;
	return s;
}

QString ApplicationSettings::getDocumentsBaseDir()
{
	return "Storage";
}

QString ApplicationSettings::getEventsDir()
{
	return "Events";
}

QString ApplicationSettings::getJournalsDir()
{
	return "Journals";
}

const QStringList& ApplicationSettings::getKeywords()
{
	return m_keywords;
}

const QStringList& ApplicationSettings::getSearchWords()
{
	return m_searchWords;
}
