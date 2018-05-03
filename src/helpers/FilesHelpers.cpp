#include "FilesHelpers.h"
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QDate>
#include <QTime>
#include <QRegularExpression>
#include <QTextCodec>
#include <QTextCursor>
#include <QTextDocument>
#include "datasources/textsources/TextFileSource.h"
#include "helpers/WordsHelpers.h"

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
	return QDate::currentDate().toString("yyyyMMdd") + QTime::currentTime().toString("hhmmss") + ".html";
}

bool readDocument(const QString& fileName, QTextDocument& document)
{
	QFile f(fileName);
	document.clear();

	if (f.open(QFile::ReadOnly))
	{
		QByteArray data = f.readAll();
		f.close();

		QTextCodec *codec = Qt::codecForHtml(data);
		QString str = codec->toUnicode(data);

		if (Qt::mightBeRichText(str))
		{
			document.setHtml(str);
		}
		else
		{
			str = QString::fromLocal8Bit(data);
			document.setPlainText(str);
		}

		return true;
	}

	return false;
}

bool isFileContainWord(const QString& fileName, const QString& word)
{
	// Поиск в тексте html (не в тегах).

	QFile f(fileName);

	QTextDocument document;

	if (readDocument(fileName, document))
	{
//		if (document.toPlainText().contains(word, Qt::CaseInsensitive))
//		{
//			return true;
//		}

		QTextCursor cursor = document.find(word, 0, 0);

		if (!cursor.isNull())
		{
			return true;
		}
	}

	return false;

	/*
	QString text = readTextFromFile(fileName);

	if (text.contains(word, Qt::CaseInsensitive))
	{
		return true;
	}
	else
	{
		return false;
	}
	*/

	/*
	QRegularExpression pattern = QRegularExpression("([А-Яа-я]|\\w)*" + word + "([А-Яа-я]|\\w)*");

	QStringList words = getWordsListFromText(readTextFromFile(fileName));

	foreach(const QString& fileWord, words)
	{
		QRegularExpressionMatchIterator matchIterator = pattern.globalMatch(fileWord);
		if (matchIterator.hasNext())
		{
			return true;
		}
	}

	return false;
	*/
}

bool isFileContainWords(const QString& fileName, const QStringList& words)
{
	// Поиск в тексте html (не в тегах).

	QFile f(fileName);

	QTextDocument document;

	if (readDocument(fileName, document))
	{
		foreach (const QString& word, words)
		{
			QTextCursor cursor = document.find(word, 0, 0);

			if (!cursor.isNull())
			{
				return true;
			}
		}
	}

	return false;
}

} // end of namespace FilesHelpers
