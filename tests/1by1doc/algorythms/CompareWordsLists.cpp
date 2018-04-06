#include "CompareWordsLists.h"
#include <QSet>
#include "../helpers/WordsHelpers.h"

CompareWordsLists::CompareWordsLists()
{

}

QMap<QString, QPair<int, int>> compareWordsLists(const QStringList& words1, const QStringList& words2)
{
	QMap<QString, int> countContainer1 = countWords(words1);
	QMap<QString, int> countContainer2 = countWords(words2);
	QSet<QString> wordsSet = QSet<QString>::fromList(countContainer1.keys());

	wordsSet.intersect(QSet<QString>::fromList(countContainer2.keys()));

	QMap<QString, QPair<int, int>> wordStatistic;

	for(auto it=wordsSet.constBegin(); it != wordsSet.constEnd(); ++it)
	{
		wordStatistic[*it] = qMakePair(countContainer1[*it], countContainer2[*it]);
	}

	return wordStatistic;
}
