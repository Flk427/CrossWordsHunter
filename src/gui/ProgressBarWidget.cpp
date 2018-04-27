#include "ProgressBarWidget.h"
#include "ui_ProgressBarWidget.h"

ProgressBarWidget::ProgressBarWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ProgressBarWidget)
{
	ui->setupUi(this);
}

ProgressBarWidget::~ProgressBarWidget()
{
	delete ui;
}

int ProgressBarWidget::value()
{
	return ui->progressBar->value();
}

void ProgressBarWidget::setValue(int value)
{
	ui->progressBar->setValue(value);
}

void ProgressBarWidget::incrementValue()
{
	setValue(value() + 1);
}

void ProgressBarWidget::setMaximum(int maximum)
{
	ui->progressBar->setMaximum(maximum);
}

void ProgressBarWidget::setState(int value, int maximum)
{
	setMaximum(maximum);
	setValue(value);
}
