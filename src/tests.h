#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QWidget>

namespace t {

class tests
{
public:
	tests();
};

void testQAX(QObject* parent = nullptr);
void testExcel1();
void testMime(QWidget* parent = nullptr);
void testLibreOffice(QObject* parent = nullptr);

}

#endif // TESTS_H
