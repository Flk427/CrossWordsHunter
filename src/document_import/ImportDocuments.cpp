#include "ImportDocuments.h"
#include <QMessageBox>
#include "helpers/FilesHelpers.h"
#include "core/DocumentsStorage.h"
#include "gui/ProgressBarWidget.h"
#include "document_import/thread/ImportOfficeFiles.h"

ImportDocuments::ImportDocuments(QObject *parent) : QObject(parent)
{

}

void ImportDocuments::start(MainWindow* owner, CWTypes::OfficeType office, CWTypes::DocumentType documentType)
{
	QStringList files = FilesHelpers::selectFiles(owner);

	if (!files.empty())
	{
		startImportFiles(owner, office, documentType, files);
	}
	else
	{
		deleteLater();
	}
}

void ImportDocuments::startImportFiles(MainWindow* owner, CWTypes::OfficeType office, CWTypes::DocumentType documentType, const QStringList& files)
{
	QThread* searchThread = new QThread(owner);
	ImportOfficeFiles* importOpenOfficeFiles = new ImportOfficeFiles(office, documentType, files);

	ProgressBarWidget* progressBarWidget = new ProgressBarWidget(owner);

	connect(progressBarWidget, &ProgressBarWidget::closed, importOpenOfficeFiles, &ImportOfficeFiles::stop, Qt::ConnectionType::DirectConnection);
	progressBarWidget->setWindowTitle("Идёт импорт...");
	progressBarWidget->setParent(owner);
	progressBarWidget->setWindowFlags(Qt::Dialog);
	progressBarWidget->setWindowModality(Qt::WindowModality::WindowModal);
	progressBarWidget->setMaximum(files.count());
	progressBarWidget->show();

	//connect(m_pb, &ProgressBarWidget::closed, wordFinder, &WordFinder::stop, Qt::ConnectionType::DirectConnection);

	importOpenOfficeFiles->moveToThread(searchThread);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, importOpenOfficeFiles, &ImportOfficeFiles::process);

	connect(importOpenOfficeFiles, &ImportOfficeFiles::progress, progressBarWidget, &ProgressBarWidget::incrementValue);
	//connect(importOpenOfficeFiles, &ImportOpenOfficeFiles::wordsFound, owner, &MainWindow::setupOccurenceTable, Qt::ConnectionType::DirectConnection);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(importOpenOfficeFiles, &ImportOfficeFiles::finished, searchThread, &QThread::quit);
	connect(importOpenOfficeFiles, &ImportOfficeFiles::finished, importOpenOfficeFiles, &ImportOfficeFiles::deleteLater);
	connect(importOpenOfficeFiles, &ImportOfficeFiles::finished, progressBarWidget, &QWidget::hide);
	connect(importOpenOfficeFiles, &ImportOfficeFiles::finished, &DocumentsStorage::Instance(), &DocumentsStorage::readDocumentsLists);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &QThread::deleteLater);
	// Удаляем прогрессбар.
	connect(searchThread, &QThread::finished, progressBarWidget, &ProgressBarWidget::deleteLater);
	// Удаляем сами себя.
	connect(searchThread, &QThread::finished, this, &ImportDocuments::deleteLater);

	searchThread->start();
}
