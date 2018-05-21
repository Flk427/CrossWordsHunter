#ifndef SEARCHWORDDIALOG_H
#define SEARCHWORDDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QThread>
#include "core/WordFinder.h"

namespace Ui {
class SearchWordDialog;
}

/*!
\brief Поиск слова.
*/
class SearchWordDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SearchWordDialog(QWidget *parent = nullptr);
	~SearchWordDialog() override;

	QString getWord() const;

private:
	Ui::SearchWordDialog *ui;

	virtual int exec() override;

public slots:
	virtual int exec(const QStringList& keywords);
};

#endif // SEARCHWORDDIALOG_H
