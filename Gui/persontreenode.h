#pragma once
#include <QVector>

class PersonTreeNode
{
public:
    PersonTreeNode(
        const QString& value,
        QVector<PersonTreeNode> children=QVector<PersonTreeNode>()
    );
private:
    QString m_value;
    QVector<PersonTreeNode> m_children;
};


