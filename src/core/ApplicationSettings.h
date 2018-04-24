#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>

// Синглтон Майерса.
class ApplicationSettings : public QObject
{
	Q_OBJECT
public:
	static ApplicationSettings& Instance();

	QString getDocumentsBaseDir();
	QString getEventsDir();
	QString getJournalsDir();
	const QStringList& getKeywords();

private:
	ApplicationSettings();  // конструктор недоступен
	~ApplicationSettings(); // и деструктор

	QStringList m_keywords;

	// необходимо также запретить копирование
	ApplicationSettings(ApplicationSettings const&); // реализация не нужна
	ApplicationSettings& operator= (ApplicationSettings const&);  // и тут

signals:
	void keywordsChanged(const QStringList& keywords);

public slots:
	void addKeyword(const QString& keyword);
};

#endif // APPLICATIONSETTINGS_H
