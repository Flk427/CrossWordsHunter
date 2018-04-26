#ifndef DOCUMENTTEXTHIGHLIGHTER_H
#define DOCUMENTTEXTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class DocumentTextHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT
public:
	enum HighlightType {htKeyword, htSearch};

	DocumentTextHighlighter(QObject* parent);

	void setKeywords(const QStringList& keywords, HighlightType highlightType);

	// QSyntaxHighlighter interface
protected:
	virtual void highlightBlock(const QString& text) override;

private:
	struct HighlightingRule
	{
		QRegularExpression pattern;
		QTextCharFormat format;
	};

	QVector<HighlightingRule> m_keywordsHighlightingRules;
	QVector<HighlightingRule> m_searchHighlightingRules;

	QRegularExpression m_commentStartExpression;
	QRegularExpression m_commentEndExpression;
	QTextCharFormat m_multiLineCommentFormat;

	void setupDefault();
	void highlightBlockRegExpExample(const QString& text);
	void highlightBlockCommentsExample(const QString& text);
};

#endif // DOCUMENTTEXTHIGHLIGHTER_H
