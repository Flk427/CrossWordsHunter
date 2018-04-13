#ifndef DOCUMENTTEXTHIGHLIGHTER_H
#define DOCUMENTTEXTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class DocumentTextHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT
public:
	DocumentTextHighlighter(QObject* parent);

	// QSyntaxHighlighter interface
protected:
	virtual void highlightBlock(const QString& text) override;

private:
	struct HighlightingRule
	{
		QRegularExpression pattern;
		QTextCharFormat format;
	};

	QVector<HighlightingRule> highlightingRules;

	QRegularExpression commentStartExpression;
	QRegularExpression commentEndExpression;

	QTextCharFormat keywordFormat;
	QTextCharFormat classFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;
};

#endif // DOCUMENTTEXTHIGHLIGHTER_H
