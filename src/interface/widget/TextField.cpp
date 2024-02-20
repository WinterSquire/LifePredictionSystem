#include "TextField.h"

#include <QLayout>

#include <QLabel>
#include <QLineEdit>

TextField::TextField(QWidget* parent)
    : QWidget(parent)
    , m_label(new QLabel(this))
    , m_text(new QLineEdit(this))
{
    setLayout(new QHBoxLayout());

    layout()->addWidget(m_label);
    layout()->addWidget(m_text);
}
