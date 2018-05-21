#ifndef WORDFINDER_H
#define WORDFINDER_H

#include <QObject>
#include "core/types.h"

class WordFinder : public QObject
{
	Q_OBJECT
public:
	explicit WordFinder(const CWTypes::DocumentType documentType, const QString& path, const QString& word, QObject *parent);

signals:
	void progress();
	void finished();

public slots:
	void process();
	void stop();

private:
	CWTypes::DocumentType m_documentType;
	QString m_path;
	QString m_word;
	bool m_stop;
};

#endif // WORDFINDER_H
