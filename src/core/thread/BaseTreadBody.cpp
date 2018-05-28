#include "BaseTreadBody.h"
#include <QDebug>

BaseTreadBody::BaseTreadBody()
	: QObject(nullptr),
	  m_stop(false)
{
}

void BaseTreadBody::process()
{
	qDebug() << "BaseTreadBody::process()";

	// Do nothing.
	emit finished();
}

void BaseTreadBody::stop()
{
	m_stop = true;
}
