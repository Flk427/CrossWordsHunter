#include "DocumentsStorage.h"
#include <QWidget>
#include <QDir>
#include "../helpers/FilesHelpers.h"
#include "ApplicationSettings.h"

DocumentsStorage::DocumentsStorage() :
	m_changed(true)
{
	updateDocumentsLists();
}

DocumentsStorage::~DocumentsStorage()
{
}

DocumentsStorage& DocumentsStorage::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static DocumentsStorage ds;
	return ds;
}

void DocumentsStorage::readDocumentsList(DocumentType documentType)
{
	QString path = getDocumentsPath(documentType);

	DocumentsListModel* documentsModel;

	if (documentType == DocumentType::Event)
	{
		documentsModel = &m_eventsModel;
	}
	else
	{
		documentsModel = &m_journalsModel;
	}

	QDir dir(path);

	documentsModel->setDocumentsList(dir.entryList(QDir::Files, QDir::Name));
}

QString DocumentsStorage::getDocumentsPath(const DocumentType documentType)
{
	ApplicationSettings& settings = ApplicationSettings::Instance();

	QString containerDirName;

	if (documentType == DocumentType::Event)
	{
		containerDirName = settings.getEventsDir();
	}
	else
	{
		containerDirName = settings.getJournalsDir();
	}

	return settings.getDocumentsBaseDir() + QDir::separator() + containerDirName;
}

DocumentsListModel*DocumentsStorage::getDocumentsListModel(const DocumentsStorage::DocumentType documentType)
{
	if (documentType == DocumentType::Event)
	{
		return &m_eventsModel;
	}
	else
	{
		return &m_journalsModel;
	}
}

QString DocumentsStorage::getNewDocumentPath(const DocumentType documentType)
{
	return getDocumentsPath(documentType) + QDir::separator() + FilesHelpers::generateFileName();
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

void DocumentsStorage::updateDocumentsLists()
{
	if (m_changed)
	{
		readDocumentsList(Event);
		readDocumentsList(Journal);
		m_changed = false;
	}
}

bool DocumentsStorage::addDocument(DocumentType documentType, const QTextDocument* document)
{
	QString fileName = getNewDocumentPath(documentType);

	if (createDocumentDir(fileName))
	{
		if (FilesHelpers::checkFileName(fileName)
			&& FilesHelpers::saveFile(document, fileName))
		{
			m_changed = true;
			updateDocumentsLists();
			emit storageUpdatedNotice(QObject::tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName)));
			return true;
		}
		else
		{
			emit storageUpdatedNotice(QObject::tr("Could not write to file \"%1\"")
								.arg(QDir::toNativeSeparators(fileName)));
			return false;
		}
	}
	else
	{
		emit storageUpdatedNotice(QObject::tr("Could not create path to file \"%1\"")
							.arg(QDir::toNativeSeparators(fileName)));
		return false;
	}
}
