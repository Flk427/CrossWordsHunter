#include "ApplicationSettings.h"

ApplicationSettings::ApplicationSettings()
{

}

ApplicationSettings::~ApplicationSettings()
{

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
