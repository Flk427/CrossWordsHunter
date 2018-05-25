#ifndef IMPORTOPENOFFICEFILES_H
#define IMPORTOPENOFFICEFILES_H

#include <QObject>
#include "core/types.h"

class ImportOpenOfficeFiles : public QObject
{
	Q_OBJECT
public:
	explicit ImportOpenOfficeFiles(CWTypes::OfficeType office, CWTypes::DocumentType documentType, QStringList files, QObject *parent = nullptr);

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

#endif // IMPORTOPENOFFICEDOCUMENTS_H
