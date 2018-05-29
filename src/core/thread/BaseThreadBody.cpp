#include "BaseThreadBody.h"
#include <QDebug>

BaseThreadBody::BaseThreadBody()
	: QObject(nullptr),
	  m_stop(false)
{
}

void BaseThreadBody::process()
{
	qDebug() << "BaseTreadBody::process()";

	// Do nothing.
	emit finished();
}

void BaseThreadBody::stop()
{
	m_stop = true;
}
