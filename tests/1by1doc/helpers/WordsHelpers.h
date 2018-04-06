#ifndef WORDSHELPERS_H
#define WORDSHELPERS_H

#include <QMap>
#include <QString>
#include <QStringList>

class WordsHelpers
{
public:
	WordsHelpers();
};

QStringList getWordsListFromText(const QString& text);
QMap<QString, int> countWords(const QStringList& wordsList, int minLength = 3);

#endif // WORDSHELPERS_H
