#ifndef COMPAREWORDSLISTS_H
#define COMPAREWORDSLISTS_H

#include <QMap>
#include <QString>
#include <QPair>

class CountCommonWords
{
public:
	CountCommonWords();
};

QMap<QString, QPair<int, int>> countCommonWords(const QStringList& words1, const QStringList& words2);

#endif // COMPAREWORDSLISTS_H
