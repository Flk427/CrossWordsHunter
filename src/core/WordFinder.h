#ifndef SEARCHWORD_H
#define SEARCHWORD_H

#include <QObject>
#include "core/types.h"

class WordFinder : public QObject
{
	Q_OBJECT
public:
	explicit WordFinder(const CWTypes::DocumentType documentType, const QString& path, const QString& word, QObject *parent);

signals:
	void fileProcessed();
	void finished();

public slots:
	void process();

private:
	CWTypes::DocumentType m_documentType;
	QString m_path;
	QString m_word;
};

#endif // SEARCHWORD_H
