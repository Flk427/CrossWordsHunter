#include "DocumentsStorage.h"
#include <QWidget>
#include <QDir>
#include "../helpers/FilesHelpers.h"
#include "ApplicationSettings.h"

DocumentsStorage& DocumentsStorage::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static DocumentsStorage ds;
	return ds;
}

DocumentsStorage::DocumentsStorage()
{
}

DocumentsStorage::~DocumentsStorage()
{
}

QString DocumentsStorage::getNewDocumentPath(const DocumentType documentType)
{
	ApplicationSettings& settings = ApplicationSettings::Instance();

	QString containerDirName;

	if (documentType == DocumentType::Event)
	{
		containerDirName = settings.getEventsDir();
	} else
	{
		containerDirName = settings.getJournalsDir();
	}

	return settings.getDocumentsBaseDir() + QDir::separator() + containerDirName + QDir::separator() + FilesHelpers::generateFileName();
}

bool DocumentsStorage::createDocumentDir(const QString& fileName)
{
	QFileInfo fi(fileName);

	if (!QDir(fi.path()).exists())
	{
		return QDir().mkdir(fi.path());
	}

	return true;
}

bool DocumentsStorage::addDocument(DocumentType documentType, QWidget* parent, const QTextDocument* document)
{
	QString fileName = getNewDocumentPath(documentType);

	if (createDocumentDir(fileName))
	{
		if (FilesHelpers::checkFileName(fileName) && FilesHelpers::saveFile(document, fileName))
		{
			emit storageUpdated(QObject::tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName)));
			return true;
		}
		else
		{
			emit storageUpdated(QObject::tr("Could not write to file \"%1\"")
								.arg(QDir::toNativeSeparators(fileName)));
			return false;
		}
	}
	else
	{
		emit storageUpdated(QObject::tr("Could not create path to file \"%1\"")
							.arg(QDir::toNativeSeparators(fileName)));
		return false;
	}
}
