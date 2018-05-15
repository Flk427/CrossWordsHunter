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

QStringList DocumentsStorage::getFilesList(const CWTypes::DocumentType documentType)
{
	QString path = getDocumentsPath(documentType);
	QDir dir(path);

	return dir.entryList(QDir::Files, QDir::Name | QDir::Reversed);
}

void DocumentsStorage::setDocumentsList(const CWTypes::DocumentType documentType, const QStringList& filesList)
{
	DocumentsListModel* documentsModel;

	if (documentType == CWTypes::DocumentType::Event)
	{
		documentsModel = &m_eventsModel;
	}
	else
	{
		documentsModel = &m_journalsModel;
	}

	documentsModel->setDocumentsList(filesList);
}

DocumentsStorage& DocumentsStorage::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static DocumentsStorage ds;
	return ds;
}

void DocumentsStorage::readAllDocumentsList(const CWTypes::DocumentType documentType)
{
	DocumentsListModel* documentsModel;

	if (documentType == CWTypes::DocumentType::Event)
	{
		documentsModel = &m_eventsModel;
	}
	else
	{
		documentsModel = &m_journalsModel;
	}

	documentsModel->setDocumentsList(getFilesList(documentType));
}

QString DocumentsStorage::getDocumentsPath(const CWTypes::DocumentType documentType)
{
	ApplicationSettings& settings = ApplicationSettings::Instance();

	QString containerDirName;

	if (documentType == CWTypes::DocumentType::Event)
	{
		containerDirName = settings.getEventsDir();
	}
	else
	{
		containerDirName = settings.getJournalsDir();
	}

	return settings.getDocumentsBaseDir() + QDir::separator() + containerDirName;
}

DocumentsListModel* DocumentsStorage::getDocumentsListModel(const CWTypes::DocumentType documentType)
{
	if (documentType == CWTypes::DocumentType::Event)
	{
		return &m_eventsModel;
	}
	else
	{
		return &m_journalsModel;
	}
}

WordsOccurenceTableModel*DocumentsStorage::getWordsOccurenceTableModel()
{
	return &m_wordsOccurenceTableModel;
}

QString DocumentsStorage::getNewDocumentsPath(const CWTypes::DocumentType documentType)
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
		readDocumentsLists();
	}
}

void DocumentsStorage::readDocumentsLists()
{
	readAllDocumentsList(CWTypes::Event);
	readAllDocumentsList(CWTypes::Journal);
	m_changed = false;
}

bool DocumentsStorage::addDocument(CWTypes::DocumentType documentType, const QTextDocument* document)
{
	QString fileName = getNewDocumentsPath(documentType);

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
