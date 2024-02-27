#include "GeneralModelView.h"

GeneralModelView::GeneralModelView(QWidget* parent)
        : QDialog(parent)
        , m_btnExecute(new ButtonExecutor(this))
        , m_btnSelectFile(new ButtonFileDialogue(this))
{
    connect(m_btnExecute, &QPushButton::pressed, this, &GeneralModelView::startTask);
    connect(m_btnExecute, &ButtonExecutor::updateUI, this, &GeneralModelView::updateUI);
}