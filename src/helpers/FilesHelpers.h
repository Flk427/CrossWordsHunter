#ifndef FILESHELPERS_H
#define FILESHELPERS_H

#include <QTextDocument>
#include "core/types.h"

namespace FilesHelpers {

class FilesHelpers
{
public:
	FilesHelpers();
};

QString selectFileName(QWidget* parent);
QString generateFileName();
bool checkFileName(const QString& fileName);
bool saveFile(const QTextDocument* document, QString fileName);
bool saveFileAs(QWidget* parent, const QTextDocument* document);
bool saveFileWithCheckName(QWidget* parent, const QTextDocument* document, QString fileName);
bool readDocument(const QString& fileName, QTextDocument& document);
bool isFileContainWord(const QString& fileName, const QString& word);
bool isFileContainWords(const QString& fileName, const QStringList& words);
QStringList selectFiles(QWidget* parent);
bool importOpenOfficeFile(CWTypes::DocumentType documentType, const QString& fileName);
CWTypes::DocumentFormat getFileFormat(const QString& fileName);

}

#endif // FILESHELPERS_H
