#include "GuiHelpers.h"
#include "gui/ProgressBarWidget.h"

GuiHelpers::GuiHelpers()
{
}

void createSearchProgressBarWidget(MainWindow* owner, BaseTreadBody* treadBody)
{
	ProgressBarWidget* progressBarWidget = new ProgressBarWidget(owner);

	progressBarWidget->setWindowTitle("Идёт поиск...");
	progressBarWidget->setParent(owner);
	progressBarWidget->setWindowFlags(Qt::Dialog);
	progressBarWidget->setWindowModality(Qt::WindowModality::WindowModal);
	progressBarWidget->show();

	QObject::connect(treadBody, &BaseTreadBody::progress, progressBarWidget, &ProgressBarWidget::incrementValue);
	QObject::connect(treadBody, &BaseTreadBody::reportState, progressBarWidget, &ProgressBarWidget::setState);
	QObject::connect(progressBarWidget, &ProgressBarWidget::closed, treadBody, &BaseTreadBody::stop, Qt::ConnectionType::DirectConnection);
	// Удаляем прогрессбар.
	QObject::connect(treadBody, &BaseTreadBody::finished, progressBarWidget, &ProgressBarWidget::deleteLater);
}
