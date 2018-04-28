#ifndef WORDSOCCURENCETABLEMODEL_H
#define WORDSOCCURENCETABLEMODEL_H

#include <QAbstractTableModel>
#include "core/types.h"


class WordsOccurenceTableModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	typedef struct
	{
		QString word;
		CWTypes::WordOccuring occuring;
	} WordInfo;

	explicit WordsOccurenceTableModel(QObject *parent = Q_NULLPTR);
	QString getWord(QModelIndex index);

	WordInfo getWordInfo(int row);

public slots:
	void setItems(const CWTypes::WordsOccuring* wordsOccuring);

private:

	//CWTypes::WordsOccuring m_wordsOccuring;

	QVector<WordInfo> m_wordsOccuring;

	// QAbstractItemModel interface
public:
	virtual int rowCount(const QModelIndex& parent) const override;
	virtual int columnCount(const QModelIndex& parent) const override;
	virtual QVariant data(const QModelIndex& index, int role) const override;

	// QAbstractItemModel interface
public:
	virtual bool insertRows(int row, int count, const QModelIndex& parent) override;
	virtual bool removeRows(int row, int count, const QModelIndex& parent) override;

	// QAbstractItemModel interface
public:
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // WORDSOCCURENCETABLEMODEL_H
