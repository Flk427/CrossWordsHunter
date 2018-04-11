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

}

#endif // FILESHELPERS_H
