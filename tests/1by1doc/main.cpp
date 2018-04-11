#include <QDebug>
#include <iostream>
#include <Windows.h>
#include "../../src/algorythms/CountCommonWords.h"
#include "../../src/helpers/WordsHelpers.h"
#include "../../src/datasources/textsources/TextFileSource.h"
#include "../../src/helpers/DevelHelpers.h"

static const char* text1 = "D:\\_private\\projects\\volkov\\CrossWords\\tests\\data\\text1.txt";
static const char* text2 = "D:\\_private\\projects\\volkov\\CrossWords\\tests\\data\\text2.txt";

void test()
{
	QStringList words1 = getWordsListFromText(readTextFromFile(text1));
	QStringList words2 = getWordsListFromText(readTextFromFile(text2));
	QMap<QString, QPair<int, int>> res = countCommonWords(words1, words2);
	saveResult(res);
}

int main(int argc, char *argv[])
{
	test();
	qDebug() << "done.";
	return 0;
}
