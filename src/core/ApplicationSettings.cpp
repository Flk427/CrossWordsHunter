#include "ApplicationSettings.h"
#include <QApplication>
#include <QDir>
#include "KeywordsListModel.h"

ApplicationSettings::ApplicationSettings()
{
	m_settings = new QSettings("config.ini", QSettings::IniFormat);
	readKeywords();
}

ApplicationSettings::~ApplicationSettings()
{
	delete m_settings;
}

QStringList ApplicationSettings::readKeywords()
{
	QStringList keywords;

	keywords.clear();

	m_settings->beginGroup("keywords");
	const QStringList childKeys = m_settings->childKeys();

	foreach (const QString &childKey, childKeys)
	{
		keywords << childKey;
	}

	m_settings->endGroup();

	return keywords;
}

void ApplicationSettings::addKeyword(const QString& keyword)
{
	if (!keyword.isEmpty())
	{
		m_settings->beginGroup("keywords");

		if (!m_settings->contains(keyword))
		{
			m_settings->setValue(keyword, "");
		}

		m_settings->endGroup();
	}
}

void ApplicationSettings::removeKeyword(const QString& keyword)
{
	if (!keyword.isEmpty())
	{
		m_settings->beginGroup("keywords");

		if (m_settings->contains(keyword))
		{
			m_settings->remove(keyword);
		}

		m_settings->endGroup();
	}
}

void ApplicationSettings::setSearchWord(const QString& searchWord)
{
	if (!searchWord.isEmpty())
	{
		m_searchWords.clear();
		m_searchWords.push_back(searchWord);
		emit searchWordsChanged(m_searchWords);
	}
	else
	{
		m_searchWords.clear();
		emit searchWordsChanged(m_searchWords);
	}
}

void ApplicationSettings::setSearchWords(const QStringList &searchWords)
{
	m_searchWords = searchWords;
}

ApplicationSettings& ApplicationSettings::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static ApplicationSettings s;
	return s;
}

QString ApplicationSettings::getDocumentsBaseDir()
{
	return QApplication::applicationDirPath() + QDir::separator() + "Storage";
}

QString ApplicationSettings::getEventsDir()
{
	return "Events";
}

QString ApplicationSettings::getJournalsDir()
{
	return "Journals";
}

const QStringList& ApplicationSettings::getSearchWords()
{
	return m_searchWords;
}
