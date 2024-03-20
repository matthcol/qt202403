#include "treemodel.h"
#include "treeitem.h"

#include <QStringList>

using namespace Qt::StringLiterals;

//! [0]
TreeModel::TreeModel(std::unique_ptr<TreeItem> data, QObject *parent)
    : QAbstractItemModel(parent)
    , rootItem(std::move(data))
{
    // setupModelData(QStringView{data}.split(u'\n'), rootItem.get());
}
//! [0]

//! [1]
TreeModel::~TreeModel() = default;
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}
//! [2]

//! [3]
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "model tree: data called on index:"
             << index
             << "and role:"
             << role;
    if (!index.isValid())
        return {};
    // access underlying data behind TreeItem
    const auto *person = static_cast<const TreeItem*>(index.internalPointer())
                                 ->data(0);
    switch (role) {
    case Qt::DisplayRole: return person->name();
    case Qt::StatusTipRole:
        return (QDate::currentDate().year() - person->birthdate().year()) > 50;
    case AgeRole:
        return (QDate::currentDate().year() - person->birthdate().year());
    }

    return {};
}
//! [3]

//! [4]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    // customizable
    return index.isValid()
               ? QAbstractItemModel::flags(index) : Qt::ItemFlags(Qt::NoItemFlags);
}
//! [4]

//! [5]
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    return orientation == Qt::Horizontal && role == Qt::DisplayRole
               ? rootItem->data(section)->name() : QVariant{};
}
//! [5]

//! [6]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return {};

    TreeItem *parentItem = parent.isValid()
                               ? static_cast<TreeItem*>(parent.internalPointer())
                               : rootItem.get();

    if (auto *childItem = parentItem->child(row))
        return createIndex(row, column, childItem);
    return {};
}
//! [6]

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};

    auto *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    return parentItem != rootItem.get()
               ? createIndex(parentItem->row(), 0, parentItem) : QModelIndex{};
}
//! [7]

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    const TreeItem *parentItem = parent.isValid()
                                     ? static_cast<const TreeItem*>(parent.internalPointer())
                                     : rootItem.get();

    return parentItem->childCount();
}
//! [8]

// void TreeModel::setupModelData(const QList<QStringView> &lines, TreeItem *parent)
// {
//     struct ParentIndentation
//     {
//         TreeItem *parent;
//         qsizetype indentation;
//     };

//     QList<ParentIndentation> state{{parent, 0}};

//     for (const auto &line : lines) {
//         qsizetype position = 0;
//         for ( ; position < line.length() && line.at(position).isSpace(); ++position) {
//         }

//         const QStringView lineData = line.sliced(position).trimmed();
//         if (!lineData.isEmpty()) {
//             // Read the column data from the rest of the line.
//             const auto columnStrings = lineData.split(u'\t', Qt::SkipEmptyParts);
//             QVariantList columnData;
//             columnData.reserve(columnStrings.count());
//             for (const auto &columnString : columnStrings)
//                 columnData << columnString.toString();

//             if (position > state.constLast().indentation) {
//                 // The last child of the current parent is now the new parent
//                 // unless the current parent has no children.
//                 auto *lastParent = state.constLast().parent;
//                 if (lastParent->childCount() > 0)
//                     state.append({lastParent->child(lastParent->childCount() - 1), position});
//             } else {
//                 while (position < state.constLast().indentation && !state.isEmpty())
//                     state.removeLast();
//             }

//             // Append a new item to the current parent's list of children.
//             auto *lastParent = state.constLast().parent;
//             lastParent->appendChild(std::make_unique<TreeItem>(columnData, lastParent));
//         }
//     }
// }


QHash<int, QByteArray> TreeModel::roleNames() const
{
    return {
        {Qt::DisplayRole, "display"},
        {Qt::EditRole, "edit"},
        {Qt::StatusTipRole, "statusTip"},
        {Role::AgeRole, "age"},
        {Role::LevelRole, "level"}
    };
}

QVariant TreeModel::getPerson(const QModelIndex &index)
{
    if (!index.isValid()) return {};
    auto *person = static_cast<const TreeItem*>(index.internalPointer())->data(0);
    return QVariant::fromValue(*person);
}
