#ifndef TYPES_H
#define TYPES_H

#include <QMap>
#include <QString>
#include <QStringList>

namespace CWTypes
{

enum DocumentType {Event, Journal};
enum DocumentFormat {Unknown, TextDocument, SpeadSheet};

enum OfficeType {OpenOffice, MicrosoftOffice};

typedef struct
{
	int firstOccuring;
	int secondOccuring;
	QStringList firstFiles;
	QStringList secondFiles;
} WordOccuring;

typedef QMap<QString, WordOccuring> WordsOccuring;

}

#endif // TYPES_H
