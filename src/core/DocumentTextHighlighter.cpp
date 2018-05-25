#include "DocumentTextHighlighter.h"

DocumentTextHighlighter::DocumentTextHighlighter(QObject* parent) : QSyntaxHighlighter(parent)
{
	//setupDefault();
}

void DocumentTextHighlighter::setKeywords(const QStringList& keywords, HighlightType highlightType)
{
	HighlightingRule rule;
	QTextCharFormat classFormat;

	if (highlightType == htKeyword)
	{
		m_keywordsHighlightingRules.clear();
	}
	else
	{
		m_searchHighlightingRules.clear();
	}

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setBackground(QBrush(QColor(Qt::black)));

	foreach(const QString& keyword, keywords)
	{
		if (highlightType == htKeyword)
		{
			classFormat.setForeground(Qt::white);
			rule.pattern = QRegularExpression("([А-Яа-я]|\\w)*" + keyword + "([А-Яа-я]|\\w)*");
		}
		else
		{
			classFormat.setForeground(QColor(0xFF, 0x80, 0x80));
			rule.pattern = QRegularExpression(keyword);
		}

		rule.format = classFormat;

		if (highlightType == htKeyword)
		{
			m_keywordsHighlightingRules.append(rule);
		}
		else
		{
			m_searchHighlightingRules.append(rule);
		}
	}

	rehighlight();
}

void DocumentTextHighlighter::highlightBlock(const QString& text)
{
	//highlightBlockRegExpExample(text);

	// Не поддерживает подсветку кириллицы через "\w+", нужно "[А-Яа-я]+".
	foreach (const HighlightingRule &rule, m_keywordsHighlightingRules)
	{
		QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

		while (matchIterator.hasNext())
		{
			QRegularExpressionMatch match = matchIterator.next();
			setFormat(match.capturedStart(), match.capturedLength(), rule.format);
		}
	}


	foreach (const HighlightingRule &rule, m_searchHighlightingRules)
	{
//		QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
//		while (matchIterator.hasNext())
//		{
//			QRegularExpressionMatch match = matchIterator.next();
//			setFormat(match.capturedStart(), match.capturedLength(), rule.format);
//		}

		int length;
		int index = text.toUpper().indexOf(rule.pattern.pattern().toUpper(), Qt::CaseInsensitive);

		while (index >= 0)
		{
			length = rule.pattern.pattern().length();
			setFormat(index, length, rule.format);
			index = text.toUpper().indexOf(rule.pattern.pattern().toUpper(), index + length, Qt::CaseInsensitive);
		}
	}

	//highlightBlockCommentsExample(text);
}

void DocumentTextHighlighter::setupDefault()
{
	HighlightingRule rule;
	QTextCharFormat keywordFormat;
	QTextCharFormat classFormat;

	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);

	QStringList keywordPatterns;

	keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
					<< "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
					<< "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
					<< "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
					<< "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
					<< "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
					<< "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
					<< "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
					<< "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
					<< "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";

	foreach (const QString &pattern, keywordPatterns)
	{
		rule.pattern = QRegularExpression(pattern);
		rule.format = keywordFormat;
		m_keywordsHighlightingRules.append(rule);
	}

	classFormat.setForeground(Qt::red);
	rule.pattern = QRegularExpression("\\bDate\\b"); // my test
	rule.format = classFormat;
	m_keywordsHighlightingRules.append(rule);

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setForeground(Qt::red);
	rule.pattern = QRegularExpression("([А-Яа-я]|\\w)*выразит([А-Яа-я]|\\w)*"); // my test
	rule.format = classFormat;
	m_keywordsHighlightingRules.append(rule);

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setForeground(Qt::red);
	rule.pattern = QRegularExpression("([А-Яа-я]|\\w)*14([А-Яа-я]|\\w)*"); // my test
	rule.format = classFormat;
	m_keywordsHighlightingRules.append(rule);

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
	rule.format = classFormat;
	m_keywordsHighlightingRules.append(rule);

	QTextCharFormat quotationFormat;

	quotationFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegularExpression("\".*\"");
	rule.format = quotationFormat;
	m_keywordsHighlightingRules.append(rule);

	QTextCharFormat functionFormat;

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(Qt::blue);
	rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat;
	m_keywordsHighlightingRules.append(rule);

	QTextCharFormat singleLineCommentFormat;

	singleLineCommentFormat.setForeground(Qt::red);
	rule.pattern = QRegularExpression("//[^\n]*");
	rule.format = singleLineCommentFormat;
	m_keywordsHighlightingRules.append(rule);

	m_multiLineCommentFormat.setForeground(Qt::red);

	m_commentStartExpression = QRegularExpression("/\\*");
	m_commentEndExpression = QRegularExpression("\\*/");
}

void DocumentTextHighlighter::highlightBlockRegExpExample(const QString& text)
{
	// Поддерживает подсветку кириллицы.
	QTextCharFormat myClassFormat;
	myClassFormat.setFontWeight(QFont::Bold);
	myClassFormat.setForeground(Qt::red);
	//QString pattern = "\\b(\\w+)\\b";
	QString pattern = "\\bсредств\\w*\\b";

	QRegExp expression(pattern);
	int index = text.indexOf(expression);

	while (index >= 0)
	{
		int length = expression.matchedLength();
		setFormat(index, length, myClassFormat);
		index = text.indexOf(expression, index + length);
	}
}

void DocumentTextHighlighter::highlightBlockCommentsExample(const QString& text)
{
	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = text.indexOf(m_commentStartExpression);

	while (startIndex >= 0) {
		QRegularExpressionMatch match = m_commentEndExpression.match(text, startIndex);
		int endIndex = match.capturedStart();
		int commentLength = 0;
		if (endIndex == -1) {
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		} else {
			commentLength = endIndex - startIndex
					+ match.capturedLength();
		}
		setFormat(startIndex, commentLength, m_multiLineCommentFormat);
		startIndex = text.indexOf(m_commentStartExpression, startIndex + commentLength);
	}
}
