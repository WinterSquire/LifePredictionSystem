#include <QMessageBox>
#include "GeneralModelView.h"

#include <QCloseEvent>

GeneralModelView::GeneralModelView(QWidget* parent)
        : QDialog(parent)
        , m_btnExecute(new ButtonExecutor(this))
        , m_btnSelectFile(new ButtonFileDialogue(this))
{
    connect(m_btnExecute, &QPushButton::pressed, this, &GeneralModelView::startTask);
    connect(m_btnExecute, &ButtonExecutor::updateUI, this, &GeneralModelView::updateUI);
    setAttribute(Qt::WA_DeleteOnClose);
    // 重载closeEvent

}

void GeneralModelView::closeEvent(QCloseEvent *event) {
    if (m_btnExecute->isTaskRunning()) {
        QMessageBox::warning(
                this,
                "任务正在进行",
                "任务正在进行，请等待任务结束后再关闭窗口！",
                QMessageBox::Yes
        );

        event->ignore();
    }
}
