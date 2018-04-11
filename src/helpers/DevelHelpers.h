#ifndef DEVELHELPERS_H
#define DEVELHELPERS_H

#include <QMap>
#include <QString>
#include <QPair>

class DevelHelpers
{
public:
	DevelHelpers();
};

void saveResult(const QMap<QString, QPair<int, int>>& wordStatistic);

#endif // DEVELHELPERS_H
