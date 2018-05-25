#ifndef IMPORTOFFICEFILES_H
#define IMPORTOFFICEFILES_H

#include <QObject>
#include "core/types.h"

class ImportOfficeFiles : public QObject
{
	Q_OBJECT
public:
	explicit ImportOfficeFiles(CWTypes::OfficeType office, CWTypes::DocumentType documentType, QStringList files, QObject *parent = nullptr);

private:
	CWTypes::OfficeType m_office;
	CWTypes::DocumentType m_documentType;
	QStringList m_files;

	bool m_stop;

signals:
	void progress();
	void finished();

public slots:
	void process();
	void stop();
};

#endif // IMPORTOFFICEFILES_H
