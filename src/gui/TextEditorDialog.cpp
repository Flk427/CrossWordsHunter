#include "TextEditorDialog.h"
#include "ui_TextEditorDialog.h"

TextEditorDialog::TextEditorDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TextEditorDialog)
{
	ui->setupUi(this);
}

TextEditorDialog::~TextEditorDialog()
{
	delete ui;
}

const QTextDocument* TextEditorDialog::getTextDocument()
{
	return ui->textEdit->document();
}
