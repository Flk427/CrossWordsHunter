#include "DocumentsStorage.h"
#include <QWidget>
#include <QDir>
#include "../helpers/FilesHelpers.h"

DocumentsStorage&DocumentsStorage::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static DocumentsStorage s;
	return s;
}

DocumentsStorage::DocumentsStorage()
{
}

DocumentsStorage::~DocumentsStorage()
{
}

bool DocumentsStorage::addDocument(DocumentType documentType, QWidget* parent, const QTextDocument* document)
{
	QString fileName = FilesHelpers::generateFileName();

	// if (documentType == DocumentType::Event) {...} else {...}

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
