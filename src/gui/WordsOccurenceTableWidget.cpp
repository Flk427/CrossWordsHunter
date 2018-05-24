#include "WordsOccurenceTableWidget.h"
#include "ui_WordsOccurenceTableWidget.h"
#include <QDebug>
#include "core/DocumentsStorage.h"
#include "core/ApplicationSettings.h"

WordsOccurenceTableWidget::WordsOccurenceTableWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::WordsOccurenceTableWidget)
{
	ui->setupUi(this);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	connect(ui->tableView, &QTableView::doubleClicked, this, &WordsOccurenceTableWidget::wordDblClicked);
}

WordsOccurenceTableWidget::~WordsOccurenceTableWidget()
{
	delete ui;
}

WordsOccurenceTableModel* WordsOccurenceTableWidget::getModel()
{
	return qobject_cast<WordsOccurenceTableModel*>(ui->tableView->model());
}

void WordsOccurenceTableWidget::setItems(const CWTypes::WordsOccuring* wordsOccuring)
{
	// TODO: записывать в модель приложения.
	WordsOccurenceTableModel* model = qobject_cast<WordsOccurenceTableModel*>(ui->tableView->model());

	if (model)
	{
		model->setItems(wordsOccuring);
	}
}

void WordsOccurenceTableWidget::wordDblClicked(QModelIndex index)
{
	QString word = getModel()->getWord(index);

	if (!word.isEmpty())
	{
		//emit searchSelectedWord(word);
		WordsOccurenceTableModel::WordInfo wordInfo = getModel()->getWordInfo(index.row());

		if (!wordInfo.word.isEmpty())
		{
			DocumentsStorage::Instance().setDocumentsList(CWTypes::Event, wordInfo.occuring.firstFiles);
			DocumentsStorage::Instance().setDocumentsList(CWTypes::Journal, wordInfo.occuring.secondFiles);
			ApplicationSettings::Instance().setSearchWord(word);
			emit wordSelectionChanged();
		}
	}
}

void WordsOccurenceTableWidget::setModel(WordsOccurenceTableModel* model)
{
	ui->tableView->setModel(model);
}
