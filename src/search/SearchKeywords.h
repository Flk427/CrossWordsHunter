#ifndef SEARCHKEYWORDS_H
#define SEARCHKEYWORDS_H

#include <QObject>
#include "gui/MainWindow.h"

class SearchKeywords : public QObject
{
	Q_OBJECT
public:
	explicit SearchKeywords();
	virtual ~SearchKeywords();

	void start(MainWindow* owner);
};

#endif // SEARCHKEYWORDS_H
