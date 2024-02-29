#include <QMessageBox>
#include "GeneralModelView.h"

#include <QCloseEvent>
#include <QVBoxLayout>

GeneralModelView::GeneralModelView(QWidget *parent, const QString &title)
        : QDialog(parent)
        , m_btnExecute(new ButtonExecutor(this))
        , m_btnSelectFile(new ButtonFileDialogue(this))
{
    this->setWindowTitle(title);
    this->setLayout(new QHBoxLayout());
    this->setFixedSize(1152, 648);

    connect(m_btnExecute, &QPushButton::pressed, this, &GeneralModelView::startTask);
    connect(m_btnExecute, &ButtonExecutor::updateUI, this, &GeneralModelView::updateUI);
    setAttribute(Qt::WA_DeleteOnClose);
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

GeneralModelView::Range GeneralModelView::GetRange(const vector<vector<double>> &data) {
    Range result { 0, 0 };

    if (data.empty()) return result;

    for (const auto &row : data) {
        for (const auto &value : row) {
            if (value < result.min) {
                result.min = value;
            }
            if (value > result.max) {
                result.max = value;
            }
        }
    }

    return result;
}

bool GeneralModelView::SetSeriesData(QScatterSeries *series, const vector<double> &data_x,
                                     const vector<double> &data_y) {
    if (series == nullptr || data_x.size() != data_y.size()) return false;

    series->clear();

    for (int i = 0; i < data_x.size(); ++i) {
        series->append(data_x[i], data_y[i]);
    }

    return true;
}
