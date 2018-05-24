#include "ImportOpenOfficeFiles.h"
#include "helpers/FilesHelpers.h"

ImportOpenOfficeFiles::ImportOpenOfficeFiles(CWTypes::DocumentType documentType, QStringList files, QObject *parent)
	: QObject(parent),
	  m_documentType(documentType),
	  m_files(files),
	  m_stop(false)
{
}

void ImportOpenOfficeFiles::process()
{
	int count(0);

	foreach (const QString& fileName, m_files)
	{
		if (m_stop) break;

		if (FilesHelpers::importOpenOfficeFile(m_documentType, fileName))
		{
			++count;
			emit progress();
		}
	}

	if (count != m_files.size())
	{
		//TODO: обрабытывать ошибки.
		// QMessageBox::warning(owner, "Завершено", "Документы импортированы", QMessageBox::StandardButton::Ok);
		// QMessageBox::warning(owner, "Внимание!", "Не удалось импортировать документы", QMessageBox::StandardButton::Ok);

	}

	//return count == m_files.size() ? true : false;
	emit finished();
}

void ImportOpenOfficeFiles::stop()
{
	m_stop = true;
}
