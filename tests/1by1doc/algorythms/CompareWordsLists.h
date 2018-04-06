#ifndef COMPAREWORDSLISTS_H
#define COMPAREWORDSLISTS_H

#include <QMap>
#include <QString>
#include <QPair>

class CompareWordsLists
{
public:
	CompareWordsLists();
};

QMap<QString, QPair<int, int>> compareWordsLists(const QStringList& words1, const QStringList& words2);

#endif // COMPAREWORDSLISTS_H
