#ifndef FILESSTORAGE_H
#define FILESSTORAGE_H

#include <QObject>
#include <QTextDocument>

#include "core/DocumentsListModel.h"
#include "core/types.h"
#include "core/WordsOccurenceTableModel.h"

class DocumentRepository : public QObject
{
	Q_OBJECT
public:
	DocumentRepository();
	virtual ~DocumentRepository();

	QString path() const;
	void setPath(const QString& path);

	QAbstractItemModel* model() const;
	void setModel(QAbstractItemModel* model);

private:
	QString m_path;
	QAbstractItemModel* m_model;
};

// Синглтон Майерса.
class DocumentsStorage : public QObject
{
	Q_OBJECT
public:
	static DocumentsStorage& Instance();

	bool addDocument(CWTypes::DocumentType documentType, const QTextDocument* document);
	QString getDocumentsPath(const CWTypes::DocumentType documentType);
	//! Возвращает модель для GUI-представлений.
	DocumentsListModel* getDocumentsListModel(const CWTypes::DocumentType documentType);
	WordsOccurenceTableModel* getWordsOccurenceTableModel();
	QString getNewDocumentsPath(const CWTypes::DocumentType documentType);
	QStringList getFilesList(const CWTypes::DocumentType documentType);
	//! Настройка отображаемых файлов. Модель сама уведомит представление об изменении.
	void setDocumentsList(const CWTypes::DocumentType documentType, const QStringList& filesList);

private:
	DocumentsStorage();  // конструктор недоступен
	~DocumentsStorage(); // и деструктор
	// необходимо также запретить копирование
	DocumentsStorage(DocumentsStorage const&); // реализация не нужна
	DocumentsStorage& operator= (DocumentsStorage const&);  // и тут

	bool m_changed;

	DocumentsListModel m_eventsModel;
	DocumentsListModel m_journalsModel;
	WordsOccurenceTableModel m_wordsOccurenceTableModel;

	void readAllDocumentsList(const CWTypes::DocumentType documentType);

	bool createDocumentDir(const QString& fileName);

signals:
	void storageUpdatedNotice(const QString& text);

public slots:
	void updateDocumentsLists();
	void readDocumentsLists();
};

#endif // FILESSTORAGE_H
