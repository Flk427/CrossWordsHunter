#ifndef FILESSTORAGE_H
#define FILESSTORAGE_H

#include <QObject>
#include <QTextDocument>

// Синглтон Майерса.
class DocumentsStorage : public QObject
{
	Q_OBJECT
public:
	enum DocumentType {Event, Journal};

	static DocumentsStorage& Instance();

	bool addDocument(DocumentType documentType, QWidget* parent, const QTextDocument* document);

private:
	DocumentsStorage();  // конструктор недоступен
	~DocumentsStorage(); // и деструктор

	// необходимо также запретить копирование
	DocumentsStorage(DocumentsStorage const&); // реализация не нужна
	DocumentsStorage& operator= (DocumentsStorage const&);  // и тут

	QString getNewDocumentPath(const DocumentType documentType);
	bool createDocumentDir(const QString& fileName);

signals:
	void storageUpdated(const QString& text);

public slots:
};

#endif // FILESSTORAGE_H
