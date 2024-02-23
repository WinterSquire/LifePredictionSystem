#include "GeneralModelView.h"

#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QPlainTextEdit>

#include "./TextField.h"

GeneralModelView::GeneralModelView(QWidget* parent)
    : QWidget(parent)
    , m_chartWidget(new DefaultChartWidget(this))
{
    this->setLayout(new QHBoxLayout());

    m_chartWidget->setFixedSize(400, 400);

    auto groupBox = new QGroupBox();
    groupBox->setLayout(new QVBoxLayout());

    // 设置按钮
    {
        auto buttonGroup = new QGroupBox();
        buttonGroup->setLayout(new QVBoxLayout());
        groupBox->layout()->addWidget(buttonGroup);

        auto btnSelectFile = new QPushButton("选择文件");
        connect(btnSelectFile, &QPushButton::pressed, [=]{
            auto dialogue = new QFileDialog(this);
            dialogue->setNameFilter("Data Files(*.csv *.txt)");
            dialogue->exec();
        });

        m_btnExecute = new QPushButton("执行");

        buttonGroup->layout()->addWidget(btnSelectFile);
        buttonGroup->layout()->addWidget(m_btnExecute);
    }

    // 设置输出
    {
        auto outputGroup = new QGroupBox();
        outputGroup->setLayout(new QVBoxLayout());
        groupBox->layout()->addWidget(outputGroup);

        m_textEpoch = new TextField();
        m_textEpoch->label()->setText("Epoch的损失和评估标准");
        m_textEpoch->text()->setText("0");
        outputGroup->layout()->addWidget(m_textEpoch);

        m_textMSE = new TextField();
        m_textMSE->label()->setText("MSE均方根误差");
        m_textMSE->text()->setText("0");
        m_textMSE->text()->setReadOnly(true);
        outputGroup->layout()->addWidget(m_textMSE);

        m_textScore = new TextField();
        m_textScore->label()->setText("Total Score");
        m_textScore->text()->setText("0");
        m_textScore->text()->setReadOnly(true);
        outputGroup->layout()->addWidget(m_textScore);
    }

    this->layout()->addWidget(m_chartWidget);
    this->layout()->addWidget(groupBox);
}

void GeneralModelView::setTotalScoreVisibility(bool value) {
    if (value)
        m_textScore->show();
    else
        m_textScore->hide();
}

void GeneralModelView::setData(const Model::Result &result) {
    m_chartWidget->actualSeries()->clear();
    m_chartWidget->forecastSeries()->clear();

    int epoch = result.sel.mse.size();
    double range_miny = 0;
    double range_maxy = 10;

    if (epoch > 0) {
        range_miny = result.sel.mse[0];
        range_maxy = result.sel.mse[0];
    }

    for (int i = 0; i < epoch; ++i) {
        double sy = result.sel.mse[i];
        double fy = result.val.mse[i];

        if (sy < range_miny) range_miny = sy;
        if (sy > range_maxy) range_maxy = sy;

        m_chartWidget->actualSeries()->append(i + 1, sy);
        m_chartWidget->forecastSeries()->append(i + 1, fy);
    }

    m_chartWidget->setAxisXRange(0, epoch);
    m_chartWidget->setAxisYRange(range_miny >= 1000 ? range_miny - 1000 : range_miny,
                                 range_maxy + 1000);
    m_chartWidget->update();

    m_textEpoch->text()->setText(QString::number(epoch));
    m_textMSE->text()->setText(QString::number(result.mean_mse));
    m_textScore->text()->setText(QString::number(result.total_score));
}
