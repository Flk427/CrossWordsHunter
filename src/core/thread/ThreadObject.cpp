#include "ThreadObject.h"
#include <QThread>
#include <QDebug>

ThreadObject::ThreadObject(BaseTreadBody* threadBody, QObject *parent)
	: QObject(parent),
	  m_threadBody(threadBody)
{
	m_thread = new QThread(parent);
	m_threadBody->moveToThread(m_thread);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(m_thread, &QThread::started, m_threadBody, &BaseTreadBody::process);
	connect(m_threadBody, &BaseTreadBody::progress, this, &ThreadObject::progress);
	// По завершению выходим из потока, и удаляем рабочий класс
	connect(m_threadBody, &BaseTreadBody::finished, m_thread, &QThread::quit);
	connect(m_threadBody, &BaseTreadBody::finished, m_threadBody, &BaseTreadBody::deleteLater);
	// Удаляем поток, после выполнения операции
	connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
	// Удаляем сами себя.
	connect(m_thread, &QThread::finished, this, &ThreadObject::deleteLater);
	connect(m_thread, &QThread::finished, this, &ThreadObject::finished);
}

ThreadObject::~ThreadObject()
{
	qDebug() << "ThreadObject::~ThreadObject()";
}

void ThreadObject::start()
{
	qDebug() << "ThreadObject::start()";
	m_thread->start();
}
