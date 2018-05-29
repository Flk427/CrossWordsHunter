#ifndef WORDSOCCURENCE_H
#define WORDSOCCURENCE_H

#include <QObject>
#include <QStringList>
#include "core/types.h"
#include "core/thread/BaseThreadBody.h"

class WordsOccurence : public BaseThreadBody
{
	Q_OBJECT
public:
	typedef QMap<QString, QPair<int, int>> CommonWordsStatistic;

	explicit WordsOccurence(const QString& dir1, const QString& dir2);

signals:
	void wordsFound(const CWTypes::WordsOccuring* wordsOccuring);

public slots:
	virtual void process();

private:
	QString m_dir1;
	QString m_dir2;
	CWTypes::WordsOccuring m_wordsOccuring;

	bool getFiles(QStringList& files1, QStringList& files2);
	void updateResult(const QMap<QString, int>& statistic, const QString& file, bool first);
};

#endif // WORDSOCCURENCE_H
