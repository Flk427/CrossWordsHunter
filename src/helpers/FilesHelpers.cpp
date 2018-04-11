#include "FilesHelpers.h"
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QDate>
#include <QTime>

namespace FilesHelpers {

FilesHelpers::FilesHelpers()
{

}

bool saveFileAs(QWidget* parent, const QTextDocument* document)
{
	QFileDialog fileDialog(parent, QObject::tr("Save as..."));
	fileDialog.setAcceptMode(QFileDialog::AcceptSave);
	QStringList mimeTypes;
	mimeTypes << "application/vnd.oasis.opendocument.text" << "text/html" << "text/plain";
	fileDialog.setMimeTypeFilters(mimeTypes);
	fileDialog.setDefaultSuffix("odt");
	if (fileDialog.exec() != QDialog::Accepted)
		return false;
	const QString fn = fileDialog.selectedFiles().first();
	return saveFileWithCheckName(parent, document, fn);
}

bool saveFileWithCheckName(QWidget* parent, const QTextDocument* document, QString fileName)
{
	if (fileName.isEmpty())
		return saveFileAs(parent, document);
	if (fileName.startsWith(QStringLiteral(":/")))
		return saveFileAs(parent, document);

	QTextDocumentWriter writer(fileName);
	bool success = writer.write(document);
	return success;
}

bool saveFile(const QTextDocument* document, QString fileName)
{
	QTextDocumentWriter writer(fileName);
	bool success = writer.write(document);
	return success;
}

QString selectFileName(QWidget* parent)
{
	QFileDialog fileDialog(parent, QObject::tr("Save as..."));
	fileDialog.setAcceptMode(QFileDialog::AcceptSave);
	QStringList mimeTypes;
	mimeTypes << "application/vnd.oasis.opendocument.text" << "text/html" << "text/plain";
	fileDialog.setMimeTypeFilters(mimeTypes);
	fileDialog.setDefaultSuffix("odt");
	if (fileDialog.exec() != QDialog::Accepted)
		return "";
	return fileDialog.selectedFiles().first();
}

bool checkFileName(const QString& fileName)
{
	if (fileName.isEmpty())
		return false;
	if (fileName.startsWith(QStringLiteral(":/")))
		return false;

	return true;
}

QString generateFileName()
{
	return QDate::currentDate().toString("yyyyMMdd") + QTime::currentTime().toString("hhmmss") + ".odt";
}

} // end of namespace FilesHelpers
