#ifndef IMPORTDOCUMENTS_H
#define IMPORTDOCUMENTS_H

#include <QObject>
#include "gui/MainWindow.h"

class ImportDocuments : public QObject
{
	Q_OBJECT
public:
	explicit ImportDocuments(QObject *parent = nullptr);

	void start(MainWindow* owner, CWTypes::OfficeType office, CWTypes::DocumentType documentType);

private:
	void startImportFiles(MainWindow* owner, CWTypes::OfficeType office, CWTypes::DocumentType documentType, const QStringList& files);

signals:

public slots:
};

#endif // IMPORTDOCUMENTS_H
