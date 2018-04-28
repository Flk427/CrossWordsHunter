#ifndef WORDSOCCURENCETABLEWIDGET_H
#define WORDSOCCURENCETABLEWIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include "core/types.h"
#include "core/WordsOccurenceTableModel.h"

namespace Ui {
class WordsOccurenceTableWidget;
}

class WordsOccurenceTableWidget : public QWidget
{
	Q_OBJECT
public:
	explicit WordsOccurenceTableWidget(QWidget *parent = 0);
	~WordsOccurenceTableWidget();

	void setModel(WordsOccurenceTableModel* model);
	WordsOccurenceTableModel* getModel();

signals:
	void searchSelectedWord(const QString& word);
	void wordSelectionChanged();

public slots:
	void setItems(const CWTypes::WordsOccuring* wordsOccuring);
	void wordDblClicked(QModelIndex index);

private:
	Ui::WordsOccurenceTableWidget *ui;
};

#endif // WORDSOCCURENCETABLEWIDGET_H
