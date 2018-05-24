#ifndef IMPORTOPENOFFICEDOCUMENTS_H
#define IMPORTOPENOFFICEDOCUMENTS_H

#include <QObject>
#include "gui/MainWindow.h"

class ImportOpenOfficeDocuments : public QObject
{
	Q_OBJECT
public:
	explicit ImportOpenOfficeDocuments(QObject *parent = nullptr);

	void start(MainWindow* owner, CWTypes::DocumentType documentType);

private:
	void startImportFiles(MainWindow* owner, CWTypes::DocumentType documentType, const QStringList& files);

signals:

public slots:
};

#endif // IMPORTOPENOFFICEDOCUMENTS_H
