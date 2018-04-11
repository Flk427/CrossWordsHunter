#include "TextFileSource.h"
#include <QFile>

TextFileSource::TextFileSource()
{

}

QString readTextFromFile(const QString& fileName)
{
	QFile file;

	file.setFileName(fileName);
	file.open(QFile::ReadOnly);

	QString fileContent(file.readAll());

	file.close();
	return fileContent;
}
