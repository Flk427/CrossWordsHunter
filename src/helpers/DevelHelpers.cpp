#include "DevelHelpers.h"
#include <QFile>
#include <QTextStream>

DevelHelpers::DevelHelpers()
{

}

void saveResult(const QMap<QString, QPair<int, int>>& wordStatistic)
{
	QFile file;
	file.setFileName("output.txt");
	file.open(QFile::WriteOnly);
	QTextStream ts(&file);

	foreach(const QString& word, wordStatistic.keys())
	{
		if (wordStatistic[word].first + wordStatistic[word].second == 2)
		{
			ts << "> ";
		}

		ts << word << ": " << (wordStatistic[word].first + wordStatistic[word].second) << " = " << wordStatistic[word].first << " + " << wordStatistic[word].second << endl;
	}
}
