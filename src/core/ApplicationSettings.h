#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QSettings>
#include "core/DocumentTextHighlighter.h"

// Синглтон Майерса.
class ApplicationSettings : public QObject
{
	Q_OBJECT
public:
	static ApplicationSettings& Instance();

	QString getDocumentsBaseDir();
	QString getEventsDir();
	QString getJournalsDir();
	const QStringList& getSearchWords();

private:
	ApplicationSettings(); // конструктор недоступен
	~ApplicationSettings(); // и деструктор

	QSettings* m_settings;

	QStringList m_searchWords;

	// необходимо также запретить копирование
	ApplicationSettings(ApplicationSettings const&); // реализация не нужна
	ApplicationSettings& operator= (ApplicationSettings const&);  // и тут

signals:
	void searchWordsChanged(const QStringList& searchWords);

public slots:
	QStringList readKeywords();
	void addKeyword(const QString& keyword);
	void removeKeyword(const QString& keyword);
	void setSearchWord(const QString& searchWord);
};

#endif // APPLICATIONSETTINGS_H
