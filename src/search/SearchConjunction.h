#ifndef SEARCHCONJUNCTION_H
#define SEARCHCONJUNCTION_H

#include <QObject>
#include "gui/MainWindow.h"

class SearchConjunction : public QObject
{
	Q_OBJECT
public:
	SearchConjunction();
	virtual ~SearchConjunction();

	void start(MainWindow* owner);
};

#endif // SEARCHCONJUNCTION_H
