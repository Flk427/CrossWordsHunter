#include "ImportOpenOfficeDocuments.h"
#include <QMessageBox>
#include "helpers/FilesHelpers.h"
#include "core/DocumentsStorage.h"
#include "gui/ProgressBarWidget.h"
#include "document_import/thread/ImportOpenOfficeFiles.h"

ImportOpenOfficeDocuments::ImportOpenOfficeDocuments(QObject *parent) : QObject(parent)
{

}

void ImportOpenOfficeDocuments::start(MainWindow* owner, CWTypes::DocumentType documentType)
{
	QStringList files = FilesHelpers::selectFiles(owner);

	if (!files.empty())
	{
		startImportFiles(owner, documentType, files);
	}
	else
	{
		deleteLater();
	}
}

void ImportOpenOfficeDocuments::startImportFiles(MainWindow* owner, CWTypes::DocumentType documentType, const QStringList& files)
{
	QThread* searchThread = new QThread(owner);
	ImportOpenOfficeFiles* importOpenOfficeFiles = new ImportOpenOfficeFiles(documentType, files);

	ProgressBarWidget* progressBarWidget = new ProgressBarWidget(owner);

	connect(progressBarWidget, &ProgressBarWidget::closed, importOpenOfficeFiles, &ImportOpenOfficeFiles::stop, Qt::ConnectionType::DirectConnection);
	progressBarWidget->setWindowTitle("Идёт импорт...");
	progressBarWidget->setParent(owner);
	progressBarWidget->setWindowFlags(Qt::Dialog);
	progressBarWidget->setWindowModality(Qt::WindowModality::WindowModal);
	progressBarWidget->setMaximum(files.count());
	progressBarWidget->show();

	//connect(m_pb, &ProgressBarWidget::closed, wordFinder, &WordFinder::stop, Qt::ConnectionType::DirectConnection);

	importOpenOfficeFiles->moveToThread(searchThread);

	// Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
	connect(searchThread, &QThread::started, importOpenOfficeFiles, &ImportOpenOfficeFiles::process);

	connect(importOpenOfficeFiles, &ImportOpenOfficeFiles::progress, progressBarWidget, &ProgressBarWidget::incrementValue);
	//connect(importOpenOfficeFiles, &ImportOpenOfficeFiles::wordsFound, owner, &MainWindow::setupOccurenceTable, Qt::ConnectionType::DirectConnection);

	// По завершению выходим из потока, и удаляем рабочий класс
	connect(importOpenOfficeFiles, &ImportOpenOfficeFiles::finished, searchThread, &QThread::quit);
	connect(importOpenOfficeFiles, &ImportOpenOfficeFiles::finished, importOpenOfficeFiles, &ImportOpenOfficeFiles::deleteLater);
	connect(importOpenOfficeFiles, &ImportOpenOfficeFiles::finished, progressBarWidget, &QWidget::hide);
	connect(importOpenOfficeFiles, &ImportOpenOfficeFiles::finished, &DocumentsStorage::Instance(), &DocumentsStorage::readDocumentsLists);

	// Удаляем поток, после выполнения операции
	connect(searchThread, &QThread::finished, searchThread, &QThread::deleteLater);
	// Удаляем прогрессбар.
	connect(searchThread, &QThread::finished, progressBarWidget, &ProgressBarWidget::deleteLater);
	// Удаляем сами себя.
	connect(searchThread, &QThread::finished, this, &ImportOpenOfficeDocuments::deleteLater);

	searchThread->start();
}
