#include "persontreenode.h"

PersonTreeNode::PersonTreeNode(const QString &value):
    m_value(value), m_children(QVector<PersonTreeNode_ptr>())
{
}

PersonTreeNode::PersonTreeNode(
    const QString& value,
    QVector<PersonTreeNode_ptr> children
) :
    m_value(value), m_children(children)
{}

const QString &PersonTreeNode::value() const
{
    return m_value;
}

void PersonTreeNode::setValue(const QString &value)
{
    m_value = value;
}

int PersonTreeNode::rowInParent() const
{
    if (m_parent == nullptr) return 0;
    // auto shared_this = std::make_shared<PersonTreeNode>(shared_from_this());
    PersonTreeNode_ptr shared_this = const_cast<PersonTreeNode_ptr>(this);
    return m_parent->m_children.indexOf(shared_this);
}

int PersonTreeNode::childrenCount() const
{
    return m_children.size();
}

PersonTreeNode_ptr PersonTreeNode::parent(){
    return m_parent;
}

PersonTreeNode_constptr PersonTreeNode::parent() const{
    return m_parent;
}

PersonTreeNode_constptr PersonTreeNode::operator[](int index) const
{
    return m_children[index];
}

PersonTreeNode_ptr& PersonTreeNode::operator[](int index)
{
    return m_children[index];
}
