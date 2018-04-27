#ifndef FILESHELPERS_H
#define FILESHELPERS_H

#include <QTextDocument>

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

}

#endif // FILESHELPERS_H
