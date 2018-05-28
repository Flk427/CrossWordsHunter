#ifndef KEYWORDSFINDER_H
#define KEYWORDSFINDER_H

#include <QObject>
#include <QDir>
#include "core/types.h"
#include "core/thread/BaseTreadBody.h"

class KeywordsFinder : public BaseTreadBody
{
	Q_OBJECT
public:
	explicit KeywordsFinder();

public slots:
	void process();

private:
	void findKeywords(const QString& path, const QStringList& files, CWTypes::DocumentType type);

	int m_count;
	int m_current;
};

#endif // KEYWORDSFINDER_H
