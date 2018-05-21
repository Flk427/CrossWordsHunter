#include "SearchWord.h"
#include "core/ApplicationSettings.h"
#include "core/DocumentsStorage.h"

SearchWord::SearchWord(QObject *parent) : QObject(parent)
{
}

SearchWord::~SearchWord()
{
}

void SearchWord::start(MainWindow* owner, const QString& word)
{
	if (!word.isEmpty())
	{
		m_pb = new ProgressBarWidget(owner);

		m_pb->setWindowTitle("Идёт поиск...");
		m_pb->setParent(owner);
		m_pb->setWindowFlags(Qt::Dialog);
		m_pb->setWindowModality(Qt::WindowModality::WindowModal);
		m_pb->show();

		ApplicationSettings::Instance().setSearchWord(word);

		QStringList events = DocumentsStorage::Instance().getFilesList(CWTypes::Event);
		QStringList journals = DocumentsStorage::Instance().getFilesList(CWTypes::Journal);

		m_pb->setMaximum(events.count() + journals.count());
		m_pb->setValue(0);

		QString eventsPath = DocumentsStorage::Instance().getDocumentsPath(CWTypes::Event);
		QString journalsPath = DocumentsStorage::Instance().getDocumentsPath(CWTypes::Journal);

		createSearchThread(CWTypes::Event, m_eventsSearchThread, m_eventsWordFinder, eventsPath, word, true);
		createSearchThread(CWTypes::Journal, m_journalsSearchThread, m_journalsWordFinder, journalsPath, word, false);

		m_eventsSearchThread->start();
	}
	else
	{
		deleteLater();
	}
}

void SearchWord::createSearchThread(const CWTypes::DocumentType documentType, QThread*& searchThread, WordFinder*& wordFinder, const QString& path, const QString& word, bool nextThread)
{
	searchThread = new QThread(this);
	wordFinder = new WordFinder(documentType, path, word, nullptr);

	wordFinder->moveToThread(searchThread);

	connect(wordFinder, &WordFinder::progress, m_pb, &ProgressBarWidget::incrementValue);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, wordFinder, &WordFinder::process);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(wordFinder, &WordFinder::finished, searchThread, &QThread::quit);
	connect(wordFinder, &WordFinder::finished, wordFinder, &WordFinder::deleteLater);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &SearchWordDialog::deleteLater);

	connect(m_pb, &ProgressBarWidget::closed, wordFinder, &WordFinder::stop, Qt::ConnectionType::DirectConnection);

	if (nextThread)
	{
		connect(wordFinder, &WordFinder::finished, this, &SearchWord::journalsSearchThreadStart);
	}
	else
	{
		// Удаляем прогрессбар.
		connect(searchThread, &QThread::finished, m_pb, &ProgressBarWidget::deleteLater);
		// Удаляем сами себя.
		connect(searchThread, &QThread::finished, this, &SearchWord::deleteLater);
	}
}

void SearchWord::journalsSearchThreadStart()
{
	m_journalsSearchThread->start();
}
