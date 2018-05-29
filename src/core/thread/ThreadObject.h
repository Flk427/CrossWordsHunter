#ifndef THREADOBJECT_H
#define THREADOBJECT_H

#include <QObject>
#include "BaseThreadBody.h"

class ThreadObject : public QObject
{
	Q_OBJECT
public:
	explicit ThreadObject(BaseThreadBody* threadBody, QObject *parent = nullptr);
	virtual ~ThreadObject();

	void start();

signals:
	void progress();
	void finished();

public slots:

private:
	QThread* m_thread;
	BaseThreadBody* m_threadBody;
};

#endif // THREADOBJECT_H
