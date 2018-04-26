#ifndef FILESSTORAGE_H
#define FILESSTORAGE_H

#include <QObject>
#include <QTextDocument>

#include "core/DocumentsListModel.h"
#include "core/types.h"

typedef struct
{
	QString word;
	int eventsWordCount;
	int journalsWordCount;
	QStringList eventsList;
	QStringList journalsList;
} WordSearchResult;

// Синглтон Майерса.
class DocumentsStorage : public QObject
{
	Q_OBJECT
public:
	static DocumentsStorage& Instance();

	bool addDocument(CWTypes::DocumentType documentType, const QTextDocument* document);
	QString getDocumentsPath(const CWTypes::DocumentType documentType);
	DocumentsListModel* getDocumentsListModel(const CWTypes::DocumentType documentType);
	QString getNewDocumentsPath(const CWTypes::DocumentType documentType);
	QStringList getFilesList(const CWTypes::DocumentType documentType);
	void setFilesList(const CWTypes::DocumentType documentType, const QStringList& filesList);

private:
	DocumentsStorage();  // конструктор недоступен
	~DocumentsStorage(); // и деструктор
	// необходимо также запретить копирование
	DocumentsStorage(DocumentsStorage const&); // реализация не нужна
	DocumentsStorage& operator= (DocumentsStorage const&);  // и тут

	bool m_changed;

	DocumentsListModel m_eventsModel;
	DocumentsListModel m_journalsModel;

	void readAllDocumentsList(const CWTypes::DocumentType documentType);

	bool createDocumentDir(const QString& fileName);

signals:
	void storageUpdatedNotice(const QString& text);

public slots:
	void updateDocumentsLists();
	void readDocumentsLists();
};

#endif // FILESSTORAGE_H
