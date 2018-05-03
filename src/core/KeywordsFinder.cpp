#include "KeywordsFinder.h"
#include "core/ApplicationSettings.h"
#include "helpers/FilesHelpers.h"
#include "core/DocumentsStorage.h"

KeywordsFinder::KeywordsFinder(QObject *parent) : QObject(parent)
{

}

void KeywordsFinder::process()
{
	m_stop = false;

	QString eventsPath = ApplicationSettings::Instance().getDocumentsBaseDir() + QDir::separator() + ApplicationSettings::Instance().getEventsDir();
	QString journalsPath = ApplicationSettings::Instance().getDocumentsBaseDir() + QDir::separator() + ApplicationSettings::Instance().getJournalsDir();

	QDir eventsDir(eventsPath);
	QDir journalsDir(journalsPath);

	QStringList eventFiles = eventsDir.entryList(QDir::Files, QDir::Name | QDir::Reversed);
	QStringList journalFiles = journalsDir.entryList(QDir::Files, QDir::Name | QDir::Reversed);

	m_current = 0;
	m_count = eventFiles.count() + journalFiles.count();

	findKeywords(eventsPath, eventFiles, CWTypes::Event);
	findKeywords(journalsPath, journalFiles, CWTypes::Journal);
	emit finished();
}

void KeywordsFinder::stop()
{
	m_stop = true;
}

void KeywordsFinder::findKeywords(const QString& path, const QStringList& files, CWTypes::DocumentType type)
{
	QStringList result;

	foreach (const QString& fileName, files)
	{
		if (m_stop)
		{
			return;
		}

		if (FilesHelpers::isFileContainWords(path + QDir::separator() + fileName, ApplicationSettings::Instance().getKeywords()))
		{
			result << fileName;
		}

		m_current++;

		emit reportState(m_current, m_count);
	}

	DocumentsStorage::Instance().setFilesList(type, result);
}
