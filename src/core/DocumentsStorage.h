#ifndef FILESSTORAGE_H
#define FILESSTORAGE_H

#include <QObject>
#include <QTextDocument>

// Синглтон Майерса.
class DocumentsStorage : public QObject
{
	Q_OBJECT
public:
	enum DocumentType {Event, Reestr};

	static DocumentsStorage& Instance();

	bool addDocument(DocumentType documentType, QWidget* parent, const QTextDocument* document);

private:
//	explicit FilesStorage(QObject *parent = nullptr);
	DocumentsStorage();  // конструктор недоступен
	~DocumentsStorage(); // и деструктор

	// необходимо также запретить копирование
	DocumentsStorage(DocumentsStorage const&); // реализация не нужна
	DocumentsStorage& operator= (DocumentsStorage const&);  // и тут

signals:
	void storageUpdated(const QString& text);

public slots:
};

#endif // FILESSTORAGE_H
