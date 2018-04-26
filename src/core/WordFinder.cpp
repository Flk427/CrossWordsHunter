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
	QStringList files = dir.entryList(QDir::Files, QDir::Name);

	QStringList result;

	foreach (const QString& fileName, files)
	{
		if (FilesHelpers::isFileContainWord(m_path + QDir::separator() + fileName, m_word))
		{
			result << fileName;
		}

		emit fileProcessed();
	}

	DocumentsStorage::Instance().setFilesList(m_documentType, result);

	qDebug() << "Файлов: " << result.count();

	emit finished();
}
