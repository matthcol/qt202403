#pragma once
#include <memory>
#include <QVector>
class PersonTreeNode;
using PersonTreeNode_ptr = PersonTreeNode*;
using PersonTreeNode_constptr = const PersonTreeNode*;

class PersonTreeNode
    //: public std::enable_shared_from_this<PersonTreeNode>
{
public:
    PersonTreeNode(
        const QString& value
    );
    PersonTreeNode(
        const QString& value,
        QVector<PersonTreeNode_ptr> children
    );
    const QString& value() const;
    void setValue(const QString& value);
    int rowInParent() const;
    int childrenCount() const;

    PersonTreeNode_ptr parent();
    PersonTreeNode_constptr parent() const;
    PersonTreeNode_constptr operator[](int index) const;
    PersonTreeNode_ptr& operator[](int index);
private:
    QString m_value;
    QVector<PersonTreeNode_ptr> m_children;
    PersonTreeNode_ptr m_parent;
};


