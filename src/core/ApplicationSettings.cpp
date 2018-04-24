#include "ApplicationSettings.h"

ApplicationSettings::ApplicationSettings()
{
	m_keywords = QStringList() << "благо" << "год";
}

ApplicationSettings::~ApplicationSettings()
{

}

void ApplicationSettings::addKeyword(const QString& keyword)
{
	m_keywords.push_back(keyword);
	emit keywordsChanged(m_keywords);
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
