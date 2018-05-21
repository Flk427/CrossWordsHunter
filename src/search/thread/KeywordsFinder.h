#ifndef KEYWORDSFINDER_H
#define KEYWORDSFINDER_H

#include <QObject>
#include <QDir>
#include "core/types.h"

class KeywordsFinder : public QObject
{
	Q_OBJECT
public:
	explicit KeywordsFinder(QObject *parent);

signals:
	void reportState(int value, int maximum);
	void finished();

public slots:
	void process();
	void stop();

private:
	void findKeywords(const QString& path, const QStringList& files, CWTypes::DocumentType type);

	bool m_stop;
	int m_count;
	int m_current;
};

#endif // KEYWORDSFINDER_H
