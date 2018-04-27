#ifndef WORDSOCCURENCE_H
#define WORDSOCCURENCE_H

#include <QObject>
#include "core/types.h"

class WordsOccurence : public QObject
{
	Q_OBJECT
public:
	explicit WordsOccurence(const QString& dir1, const QString& dir2, QObject *parent);

signals:
	void progress(int current, int total);
	void finished();

public slots:
	void process();

private:
	QString m_dir1;
	QString m_dir2;
};

#endif // WORDSOCCURENCE_H
