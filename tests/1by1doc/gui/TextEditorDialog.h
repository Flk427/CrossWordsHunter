#ifndef TEXTEDITORDIALOG_H
#define TEXTEDITORDIALOG_H

#include <QDialog>
#include <QTextDocument>

namespace Ui {
class TextEditorDialog;
}

class TextEditorDialog : public QDialog
{
	Q_OBJECT

public:
	explicit TextEditorDialog(QWidget *parent = 0);
	~TextEditorDialog();

	const QTextDocument* getTextDocument();

private:
	Ui::TextEditorDialog *ui;
};

#endif // TEXTEDITORDIALOG_H
