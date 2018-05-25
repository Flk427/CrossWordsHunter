#include "ImportOpenOfficeFiles.h"
#include "helpers/FilesHelpers.h"

ImportOpenOfficeFiles::ImportOpenOfficeFiles(CWTypes::OfficeType office, CWTypes::DocumentType documentType, QStringList files, QObject *parent)
	: QObject(parent),
	  m_office(office),
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

		if (m_office == CWTypes::OfficeType::OpenOffice)
		{
			if (FilesHelpers::importOpenOfficeFile(m_documentType, fileName))
			{
				++count;
				emit progress();
			}
			else
			{
				break;
			}
		}
		else if (m_office == CWTypes::OfficeType::MicrosoftOffice)
		{
			if (FilesHelpers::importMicrosoftOfficeFile(m_documentType, fileName))
			{
				++count;
				emit progress();
			}
			else
			{
				break;
			}
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
