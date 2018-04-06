#ifndef TEXTFILESOURCE_H
#define TEXTFILESOURCE_H

#include <QString>

class TextFileSource
{
public:
	TextFileSource();
};

QString readTextFromFile(const QString& fileName);

#endif // TEXTFILESOURCE_H
