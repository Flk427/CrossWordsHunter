#include "SearchWordDialog.h"
#include "ui_SearchWordDialog.h"
#include <QCloseEvent>
#include "core/DocumentsStorage.h"
#include "core/ApplicationSettings.h"

SearchWordDialog::SearchWordDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SearchWordDialog)
{
	ui->setupUi(this);

	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SearchWordDialog::accept);
	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	ui->progressWidget->setVisible(false);
}

SearchWordDialog::~SearchWordDialog()
{
	delete ui;
}

QString SearchWordDialog::getWord() const
{
	return ui->comboBox->currentText();
}


int SearchWordDialog::exec()
{
	return QDialog::exec();
}

int SearchWordDialog::exec(const QStringList& keywords)
{
	setWindowTitle("Поиск фрагмента текста");

	ui->frame->setVisible(true);
	ui->progressWidget->setVisible(false);

	ui->comboBox->clear();
	ui->comboBox->insertItems(0, keywords);
	ui->comboBox->setCurrentIndex(-1);
	ui->comboBox->setFocus();
	return exec();
}
