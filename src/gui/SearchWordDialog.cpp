#include "SearchWordDialog.h"
#include "ui_SearchWordDialog.h"
#include <QCloseEvent>
#include "core/DocumentsStorage.h"
#include "core/ApplicationSettings.h"

SearchWordDialog::SearchWordDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SearchWordDialog)
{
	ui->setupUi(this);

	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SearchWordDialog::startSearch);
	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	ui->progressWidget->setVisible(false);
}

SearchWordDialog::~SearchWordDialog()
{
	delete ui;
}

void SearchWordDialog::startSearch()
{
	startSearchWord(ui->comboBox->currentText());
}

void SearchWordDialog::startSearchWord(const QString& word)
{
	if (!word.isEmpty())
	{
		if (!isVisible())
		{
			show();
		}

		ApplicationSettings::Instance().setSearchWord(word);

		m_canClose = false;

		ui->frame->setVisible(false);
		ui->progressWidget->setVisible(true);

		QStringList events = DocumentsStorage::Instance().getFilesList(CWTypes::Event);
		QStringList journals = DocumentsStorage::Instance().getFilesList(CWTypes::Journal);

		ui->progressWidget->setMaximum(events.count() + journals.count());
		ui->progressWidget->setValue(0);

		QString eventsPath = DocumentsStorage::Instance().getDocumentsPath(CWTypes::Event);
		QString journalsPath = DocumentsStorage::Instance().getDocumentsPath(CWTypes::Journal);

		createSearchThread(CWTypes::Event, m_eventsSearchThread, m_eventsWordFinder, eventsPath, word, true);
		createSearchThread(CWTypes::Journal, m_journalsSearchThread, m_journalsWordFinder, journalsPath, word, false);

		m_eventsSearchThread->start();
	}
}

void SearchWordDialog::journalsSearchThreadStart()
{
	m_journalsSearchThread->start();
}

void SearchWordDialog::searchFinished()
{
	accept();
}


int SearchWordDialog::exec()
{
	m_canClose = true;
	return QDialog::exec();
}

void SearchWordDialog::createSearchThread(
		const CWTypes::DocumentType documentType,
		QThread*& searchThread,
		WordFinder*& wordFinder,
		const QString& path,
		const QString& word,
		bool nextThread)
{
	searchThread = new QThread(this);
	wordFinder = new WordFinder(documentType, path, word, nullptr);

	wordFinder->moveToThread(searchThread);

	connect(wordFinder, &WordFinder::progress, ui->progressWidget, &ProgressBarWidget::incrementValue);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, wordFinder, &WordFinder::process);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(wordFinder, &WordFinder::finished, searchThread, &QThread::quit);
	connect(wordFinder, &WordFinder::finished, wordFinder, &WordFinder::deleteLater);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &SearchWordDialog::deleteLater);

	if (nextThread)
	{
		connect(wordFinder, &WordFinder::finished, this, &SearchWordDialog::journalsSearchThreadStart);
	}
	else
	{
		connect(wordFinder, &WordFinder::finished, this, &SearchWordDialog::searchFinished);
	}
}

int SearchWordDialog::exec(const QStringList& keywords)
{
	ui->frame->setVisible(true);
	ui->progressWidget->setVisible(false);

	ui->comboBox->clear();
	ui->comboBox->insertItems(0, keywords);
	ui->comboBox->setCurrentIndex(-1);
	ui->comboBox->setFocus();
	return exec();
}

void SearchWordDialog::closeEvent(QCloseEvent* event)
{
	if (m_canClose)
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}
