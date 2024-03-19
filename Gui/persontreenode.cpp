#include "persontreenode.h"

PersonTreeNode::PersonTreeNode(
    const QString& value,
    QVector<PersonTreeNode> children
) :
    m_value(value), m_children(children)
{}
