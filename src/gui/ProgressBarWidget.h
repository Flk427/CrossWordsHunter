#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include <QWidget>

namespace Ui {
class ProgressBarWidget;
}

class ProgressBarWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ProgressBarWidget(QWidget *parent = 0);
	~ProgressBarWidget();

	int value();

signals:
	void closed();

public slots:
	void setValue(int value);
	void incrementValue();
	void setMaximum(int maximum);
	void setState(int value, int maximum);

private:
	Ui::ProgressBarWidget *ui;

	// QWidget interface
protected:
	virtual void closeEvent(QCloseEvent* event) override;
};

#endif // PROGRESSBARWIDGET_H
