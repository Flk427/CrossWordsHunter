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

private:
	ApplicationSettings();  // конструктор недоступен
	~ApplicationSettings(); // и деструктор

	// необходимо также запретить копирование
	ApplicationSettings(ApplicationSettings const&); // реализация не нужна
	ApplicationSettings& operator= (ApplicationSettings const&);  // и тут

signals:

public slots:
};

#endif // APPLICATIONSETTINGS_H
