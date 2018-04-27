#ifndef TYPES_H
#define TYPES_H

#include <QMap>
#include <QString>
#include <QStringList>

namespace CWTypes
{

enum DocumentType {Event, Journal};

typedef struct
{
	int eventsOccuring;
	int journalsOccuring;
	QStringList events;
	QStringList journals;
} WordOccuring;

typedef QMap<QString, WordOccuring> WordsOccuring;

}

#endif // TYPES_H
