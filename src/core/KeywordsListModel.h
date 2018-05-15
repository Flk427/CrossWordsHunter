#ifndef KEYWORDSLISTMODEL_H
#define KEYWORDSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

// Синглтон Майерса.
class KeywordsListModel : public QAbstractListModel
{
	Q_OBJECT
public:
	static KeywordsListModel& Instance();

	QStringList keywords() const;
	void addKeyword(const QString& keyword);

signals:
	void keywordsListChanged(const QStringList& m_keywords);

public slots:

	// QAbstractItemModel interface
public:
	virtual int rowCount(const QModelIndex&) const override;
	virtual QVariant data(const QModelIndex& index, int role) const override;

private:
	explicit KeywordsListModel(QObject *parent = nullptr); // конструктор недоступен
	~KeywordsListModel(); // и деструктор
	// необходимо также запретить копирование
	KeywordsListModel(KeywordsListModel const&); // реализация не нужна
	KeywordsListModel& operator= (KeywordsListModel const&);  // и тут

	QStringList m_keywords;

	void readKeywords();
};

#endif // KEYWORDSLISTMODEL_H
