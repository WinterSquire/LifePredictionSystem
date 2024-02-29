#include "TextField.h"

#include <QLayout>

#include <QLabel>
#include <QLineEdit>

TextField::TextField(QWidget* parent, const QString& label, const QString& text, bool readOnly)
    : QWidget(parent)
    , m_label(new QLabel(this))
    , m_text(new QLineEdit(this))
{
    // 设置属性
    m_label->setText(label);
    m_text->setText(text);
    m_text->setReadOnly(readOnly);

    // 设置布局
    setLayout(new QHBoxLayout());

    layout()->addWidget(m_label);
    layout()->addWidget(m_text);
}
