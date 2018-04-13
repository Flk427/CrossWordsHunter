#ifndef FILESSTORAGE_H
#define FILESSTORAGE_H

#include <QObject>
#include <QTextDocument>

#include "core/DocumentsListModel.h"

// Синглтон Майерса.
class DocumentsStorage : public QObject
{
	Q_OBJECT
public:
	enum DocumentType {Event, Journal};

	static DocumentsStorage& Instance();

	bool addDocument(DocumentType documentType, const QTextDocument* document);
	QString getDocumentsPath(const DocumentType documentType);
	DocumentsListModel* getDocumentsListModel(const DocumentType documentType);

private:
	DocumentsStorage();  // конструктор недоступен
	~DocumentsStorage(); // и деструктор

	bool m_changed;

	DocumentsListModel m_eventsModel;
	DocumentsListModel m_journalsModel;

	// необходимо также запретить копирование
	DocumentsStorage(DocumentsStorage const&); // реализация не нужна
	DocumentsStorage& operator= (DocumentsStorage const&);  // и тут

	void readDocumentsList(DocumentType documentType);

	QString getNewDocumentPath(const DocumentType documentType);
	bool createDocumentDir(const QString& fileName);

signals:
	void storageUpdatedNotice(const QString& text);

public slots:
	void updateDocumentsLists();
};

#endif // FILESSTORAGE_H
