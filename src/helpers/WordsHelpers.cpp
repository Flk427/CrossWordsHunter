#include "WordsHelpers.h"

WordsHelpers::WordsHelpers()
{

}

QStringList getWordsListFromText(const QString& text)
{
	//QRegExp separator("(\\s+|\\n+|\\.|\\-|\\(|\\)|\\:|\"|,|#|/|\\!)");
	QRegExp separator("(\\W+|_+)"); // \W - Любой символ, кроме букв, цифр и символа подчёркивания.
	return text.split(separator, QString::SkipEmptyParts);
}

QMap<QString, int> countWords(const QStringList& wordsList, int minLength)
{
	QMap<QString, int> countContainer;

	foreach(const QString& word, wordsList)
	{
		if (word.length() >= minLength)
		{
			countContainer[word.toUpper()] = countContainer[word.toUpper()] + 1;
		}
	}

	return countContainer;
}
