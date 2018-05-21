#ifndef WORDSOCCURENCE_H
#define WORDSOCCURENCE_H

#include <QObject>
#include <QStringList>
#include "core/types.h"

class WordsOccurence : public QObject
{
	Q_OBJECT
public:
	typedef QMap<QString, QPair<int, int>> CommonWordsStatistic;

	explicit WordsOccurence(const QString& dir1, const QString& dir2, QObject *parent);

signals:
	void progress(int current, int total);
	void finished();
	void wordsFound(const CWTypes::WordsOccuring* wordsOccuring);

public slots:
	void process();
	void stop();

private:
	bool m_stop;
	QString m_dir1;
	QString m_dir2;
	CWTypes::WordsOccuring m_wordsOccuring;

	bool getFiles(QStringList& files1, QStringList& files2);
	void updateResult(const QMap<QString, int>& statistic, const QString& file, bool first);
};

#endif // WORDSOCCURENCE_H
