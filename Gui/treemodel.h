#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <memory>

class TreeItem;

//! [0]
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(TreeModel)

    // custom roles
    enum Role {
        AgeRole = Qt::UserRole,
        LevelRole = Qt::UserRole + 1
    };

    explicit TreeModel(std::unique_ptr<TreeItem> data, QObject *parent = nullptr);
    ~TreeModel() override;

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = {}) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    QVariant getPerson(const QModelIndex& index);
private:
    // static void setupModelData(const QList<QStringView> &lines, TreeItem *parent);

    std::unique_ptr<TreeItem> rootItem;


};
//! [0]

#endif // TREEMODEL_H
