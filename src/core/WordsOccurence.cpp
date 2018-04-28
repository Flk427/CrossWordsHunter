#include "WordsOccurence.h"
#include <QDir>
#include <QTextDocument>
#include <QDebug>
#include "algorythms/CountCommonWords.h"
#include "helpers/FilesHelpers.h"
#include "helpers/WordsHelpers.h"

WordsOccurence::WordsOccurence(const QString& dir1, const QString& dir2, QObject *parent)
	: QObject(parent),
	  m_dir1(dir1),
	  m_dir2(dir2)
{
	qRegisterMetaType<CWTypes::WordsOccuring>("CWTypes::WordsOccuring");
}

void WordsOccurence::process()
{
	m_stop = false;

	QStringList files1;
	QStringList files2;

	m_wordsOccuring.clear();

	if (getFiles(files1, files2))
	{
		QTextDocument document1;
		QTextDocument document2;

		int current(0);
		int total = files1.count() + files2.count();

		foreach (const QString& file1, files1)
		{
			if (m_stop)
			{
				emit finished();
				qDebug() << "Stop";
				return;
			}

			if (FilesHelpers::readDocument(m_dir1 + QDir::separator() + file1, document1))
			{
				QMap<QString, int> result = countWords(getWordsListFromText(document1.toPlainText()), 5);

				if (result.count() != 0)
				{
					updateResult(result, file1, true);
				}
			}

			current++;
			emit progress(current, total);
		}

		foreach (const QString& file2, files2)
		{
			if (m_stop)
			{
				emit finished();
				qDebug() << "Stop";
				return;
			}

			if (FilesHelpers::readDocument(m_dir2 + QDir::separator() + file2, document2))
			{
				QMap<QString, int> result = countWords(getWordsListFromText(document2.toPlainText()), 5);

				if (result.count() != 0)
				{
					updateResult(result, file2, false);
				}
			}

			current++;
			emit progress(current, total);
		}
	}

	foreach (const QString& word, m_wordsOccuring.keys())
	{
		if (m_wordsOccuring[word].firstOccuring
			&& m_wordsOccuring[word].secondOccuring
			&& m_wordsOccuring[word].firstOccuring < 5
			&& m_wordsOccuring[word].secondOccuring < 5)
		{
			qDebug() << word << m_wordsOccuring[word].firstOccuring << m_wordsOccuring[word].secondOccuring;
		}
	}

	emit wordsFound(&m_wordsOccuring);
	emit finished();
}

void WordsOccurence::stop()
{
	m_stop = true;
}

bool WordsOccurence::getFiles(QStringList& files1, QStringList& files2)
{
	QDir dir1(m_dir1);
	QDir dir2(m_dir2);

	files1 = dir1.entryList(QDir::Files, QDir::Name);
	files2 = dir2.entryList(QDir::Files, QDir::Name);

	if (files1.empty() || files2.empty())
	{
		return false;
	}

	return true;
}

void WordsOccurence::updateResult(const QMap<QString, int>& statistic, const QString& file, bool first)
{
	foreach (const QString& word, statistic.keys())
	{
		if (m_wordsOccuring.contains(word))
		{
			if (first)
			{
				m_wordsOccuring[word].firstOccuring += statistic[word];
				m_wordsOccuring[word].firstFiles.append(file);
			}
			else
			{
				m_wordsOccuring[word].secondOccuring += statistic[word];
				m_wordsOccuring[word].secondFiles.append(file);
			}
		}
		else
		{
			if (first)
			{
				m_wordsOccuring[word].firstOccuring = statistic[word];
				m_wordsOccuring[word].secondOccuring = 0;
				m_wordsOccuring[word].firstFiles = QStringList(file);
				m_wordsOccuring[word].secondFiles = QStringList();
			}
			else
			{
				m_wordsOccuring[word].firstOccuring = 0;
				m_wordsOccuring[word].secondOccuring = statistic[word];
				m_wordsOccuring[word].firstFiles = QStringList();
				m_wordsOccuring[word].secondFiles = QStringList(file);
			}
		}
	}
}
