#include "WordFinder.h"
#include <QDir>
#include <QDebug>
#include "core/DocumentsStorage.h"
#include "helpers/FilesHelpers.h"

WordFinder::WordFinder(const CWTypes::DocumentType documentType, const QString& path, const QString& word, QObject *parent) :
	QObject(parent),
	m_documentType(documentType),
	m_path(path),
	m_word(word)
{
}

void WordFinder::process()
{
	QDir dir(m_path);
	QStringList files = dir.entryList(QDir::Files, QDir::Name | QDir::Reversed);
	QStringList result;

	foreach (const QString& fileName, files)
	{
		if (FilesHelpers::isFileContainWord(m_path + QDir::separator() + fileName, m_word))
		{
			result << fileName;
		}

		emit progress();
	}

	DocumentsStorage::Instance().setDocumentsList(m_documentType, result);
	emit finished();
}
