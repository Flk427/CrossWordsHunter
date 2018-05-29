#include "GuiHelpers.h"
#include "gui/ProgressBarWidget.h"

GuiHelpers::GuiHelpers()
{
}

void createSearchProgressBarWidget(MainWindow* owner, BaseThreadBody* treadBody)
{
	ProgressBarWidget* progressBarWidget = new ProgressBarWidget(owner);

	progressBarWidget->setWindowTitle("Идёт поиск...");
	progressBarWidget->setParent(owner);
	progressBarWidget->setWindowFlags(Qt::Dialog);
	progressBarWidget->setWindowModality(Qt::WindowModality::WindowModal);
	progressBarWidget->show();

	QObject::connect(treadBody, &BaseThreadBody::progress, progressBarWidget, &ProgressBarWidget::incrementValue);
	QObject::connect(treadBody, &BaseThreadBody::reportState, progressBarWidget, &ProgressBarWidget::setState);
	QObject::connect(progressBarWidget, &ProgressBarWidget::closed, treadBody, &BaseThreadBody::stop, Qt::ConnectionType::DirectConnection);
	// Удаляем прогрессбар.
	QObject::connect(treadBody, &BaseThreadBody::finished, progressBarWidget, &ProgressBarWidget::deleteLater);
}
