#include <QCoreApplication>
#include <iostream>
#include <Windows.h>
#include "algorythms/CountCommonWords.h"
#include "helpers/WordsHelpers.h"
#include "datasources/textsources/TextFileSource.h"
#include "helpers/DevelHelpers.h"

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
//	QCoreApplication a(argc, argv);
//	return a.exec();

	test();
	std::cout << "done." << std::endl;
	return 0;
}
