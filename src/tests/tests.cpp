#include "tests.h"

#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QAxWidget>
#include <QApplication>

#include <QMimeDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QUrl>
#include <QTextEdit>

#include "core/thread/BaseThreadBody.h"
#include "core/thread/ThreadObject.h"

namespace t {

tests::tests()
{

}

void testQAX(QObject* parent)
{
	QAxObject *loServiceManager = new QAxObject( "com.sun.star.ServiceManager", parent);
	QAxObject *loDesctop = new QAxObject( "com.sun.star.frame.Desktop", parent);
}

void testExcel1()
{
	QString strVal;
	const char* cp = "Range(B25)";

	QAxWidget excel("Excel.Application");

	// because I want to read the file - not display it.
	//excel.setProperty("Visible", false);

	QAxObject *workbooks = excel.querySubObject("WorkBooks");

	if (workbooks != nullptr)
	{
		workbooks->dynamicCall("Open (const QString&)", QApplication::applicationDirPath()+"/ttt.xls");
		QAxObject *workbook = excel.querySubObject("ActiveWorkBook");

		// I need data from the 2nd worksheet (worksheets are numbered starting from 1)
		QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

		// Read fom the second worksheet the contents of cell E11
		QAxObject *range = worksheet->querySubObject(cp);
		QVariant v = range->property("Value");
		QString s = v.toString() ;
		qDebug() << "main() | s1 is" << s << s.isEmpty() << v.isNull() << v.isValid() << v.typeName() << v.canConvert<QString>();


		QAxObject* cell = worksheet->querySubObject("Cells(QVariant,QVariant)", 12, 1);
		QVariant vv = cell->property("Value");
		QString ss = vv.toString() ;
		qDebug() << "main() | s2 is" << ss << ss.isEmpty() << vv.isNull() << vv.isValid() << vv.typeName() << vv.canConvert<QString>();

		// close the excel file
		excel.dynamicCall("Quit (void)");
	}
}

QString mimeType(const QString &filePath)
{
	return QMimeDatabase().mimeTypeForFile(filePath).name();
}

void testMime(QWidget* parent)
{
	// "application/vnd.openxmlformats-officedocument.wordprocessingml.document"
	QString f1 = "*.docx";
	//"application/rtf"
	QString f2 = "*.rtf";
	//"application/msword"
	QString f3 = "*._doc";
	//"application/msword"
	QString f4 = "*.doc";
	//"message/rfc822"
	QString f5 = "*.eml";
	//"application/zip"
	QString f6 = "*._docx";
	//"application/vnd.oasis.opendocument.text"
	QString f7 = "*.odt";
	//"application/vnd.oasis.opendocument.spreadsheet"
	QString f8 = "*.ods";
	//"application/octet-stream"
	QString f9 = "gdbus-nonce-file";
	//"application/octet-stream" (no file)
	QString f10 = "321";
	//"application/vnd.ms-excel"
	QString f11 = "*.xls";
	//"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"
	QString f12 = "*.xlsx";

	qDebug() << mimeType(f1);
	qDebug() << mimeType(f2);
	qDebug() << mimeType(f3);
	qDebug() << mimeType(f4);
	qDebug() << mimeType(f5);
	qDebug() << mimeType(f6);
	qDebug() << mimeType(f7);
	qDebug() << mimeType(f8);
	qDebug() << mimeType(f9);
	qDebug() << mimeType(f10);
	qDebug() << mimeType(f11);
	qDebug() << mimeType(f12);

	QString mime = mimeType(f10);
	//QMessageBox::information(parent, "testMime", mime, QMessageBox::StandardButton::Ok);
}

void saveAs(QAxObject* serviceManager, QAxObject* document)
{
	QVariantList propList;

	QAxObject* propertyFilterName = serviceManager->querySubObject("Bridge_GetStruct(string)", "com.sun.star.beans.PropertyValue");

	if (propertyFilterName)
	{
		// если всё хорошо - записываем туда пару "Hidden" - true
		propertyFilterName->setProperty("name", "FilterName");
		//propertyFilterName->setProperty("Value", "MS Excel 97");
//		propertyFilterName->setProperty("value", "Text - txt - csv (StarCalc)");
//		propertyFilterName->setProperty("Handle ", -1);
//		propertyFilterName->setProperty("State", 0);
		propertyFilterName->setProperty("value", "HTML (StarCalc)");
		//		// и в список ее
		propList << propertyFilterName->asVariant();
		qDebug() << propList;
	}

//	QAxObject* propertyFilterOptions = serviceManager->querySubObject("Bridge_GetStruct(string)", "com.sun.star.beans.PropertyValue");
//	if (propertyFilterOptions)
//	{
//		propertyFilterOptions->setProperty("name", "FilterOptions");
//		propertyFilterOptions->setProperty("value", "44,34,0,1");
//		//		// и в список ее
//		propList << propertyFilterOptions->asVariant();
//		qDebug() << propList;
//	}

	QString url = QUrl::fromLocalFile("D:\\test.csv").toString();
//	QMessageBox::information(nullptr, "test LO", url, QMessageBox::StandardButton::Ok);

	QAxObject* result = document->querySubObject("storeToUrl(string, sequence)", QVariant(url), propList);
}

void testLibreOffice(QObject* parent)
{
	QAxObject* serviceManager = new QAxObject("com.sun.star.ServiceManager", parent);

//	static QTextEdit te;
//	te.setText(serviceManager->generateDocumentation());
//	te.show();

	QAxObject* desktop = serviceManager->querySubObject("createInstance(const QString&)", "com.sun.star.frame.Desktop");

	if (desktop)
	{
		// берём структуру com.sun.star.beans.PropertyValue
		QAxObject* propertyValue = serviceManager->querySubObject("Bridge_GetStruct(string)", "com.sun.star.beans.PropertyValue");

		QVariantList vl;

		if (propertyValue)
		{
			// если всё хорошо - записываем туда пару "Hidden" - true
//			propertyValue->setProperty("Hidden", true);
			propertyValue->setProperty("Name", "Hidden");
			propertyValue->setProperty("Value", true);
			//		// и в список ее
			vl << propertyValue->asVariant();
			qDebug() << vl;
		}

		QString url = QUrl::fromLocalFile("test.ods").toString();
		//QMessageBox::information(dynamic_cast<QWidget*>(parent), "test LO", url, QMessageBox::StandardButton::Ok);

		// пытаемся загрузить документ. Он грузиться, никаких исключений
		// не выдает, но окно writer'а показывает.
		QAxObject* document = desktop->querySubObject("LoadComponentFromURL(string, string, long, sequence)", QVariant(url), "_blank", 0, vl);

		//QAxObject* setvis = desktop->querySubObject("SetVisible(boolean)", false);

		//QAxObject *OO_Doc = desktop->querySubObject("LoadComponentFromURL(string, string, long, sequence)", QVariant("private:factory/scalc"), "_blank", 0, vl);

		//QAxObject* doc = desktop->querySubObject("getCurrentComponent()"); // x/z

		if (document)
		{
			saveAs(serviceManager, document);

			/*
			QAxObject* sheets = document->querySubObject("getSheets()");

			// Получение активного листа.
			QAxObject* currentController = document->querySubObject("CurrentController()");
			QAxObject* activeSheet = currentController->querySubObject("ActiveSheet()");

			QVariant sheetsCount = sheets->dynamicCall("getCount()");

			QVariant sheetNames = sheets->dynamicCall("getElementNames()");
			qDebug() << sheetNames;


			QAxObject* sheet = sheets->querySubObject("getByName(const QString&)", QVariant("Лист1"));

			if (sheet)
			{
				QAxObject* cell = sheet->querySubObject("getCellByPosition(long, long)", 2, 2); //nw
				//QAxObject* cell = sheet->querySubObject("getCellRangeByName(const QString&)", QVariant("B2:B2")); //nw

//				static QTextEdit te;
//				te.setText(sheet->generateDocumentation());
//				te.show();
				//QMessageBox::information(dynamic_cast<QWidget*>(parent), "test LO", url, QMessageBox::StandardButton::Ok);

				//cell->querySubObject("setFormula(string)", "1234567890");

				QVariant cellValue = cell->dynamicCall("getFormula()");
				qDebug() << cellValue;

			}
			*/

			document->querySubObject("Dispose()");
		}
	}

	delete serviceManager;
}

class TestTreadBody : public BaseThreadBody
{
public:
	TestTreadBody()
	{
		::BaseThreadBody();

		qDebug() << "TestTreadBody()";
	}

	virtual ~TestTreadBody()
	{
		qDebug() << "~TestTreadBody()";
	}

public slots:
	virtual void process()
	{
		qDebug() << "process()";

		BaseThreadBody::process();
	}
};

void threadTest()
{
	TestTreadBody* b = new TestTreadBody();

	ThreadObject* t = new ThreadObject(b);
	t->start();
}

}
