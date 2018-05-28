#ifndef ABSTRACTTREADBODY_H
#define ABSTRACTTREADBODY_H

#include <QObject>

class BaseTreadBody : public QObject
{
	Q_OBJECT
public:
	explicit BaseTreadBody();

signals:
	void progress();
	void reportState(int value, int maximum);
	void finished();

public slots:
	virtual void process();
	virtual void stop();

protected:
	bool m_stop;
};

#endif // ABSTRACTTREADBODY_H
