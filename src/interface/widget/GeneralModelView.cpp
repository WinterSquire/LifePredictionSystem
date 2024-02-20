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
        buttonGroup->layout()->addWidget(btnSelectFile);
    }

    // 设置输出
    {
        auto outputGroup = new QGroupBox();
        outputGroup->setLayout(new QVBoxLayout());
        groupBox->layout()->addWidget(outputGroup);

        auto textEpoch = new TextField();
        textEpoch->label()->setText("Epoch的损失和评估标准");
        textEpoch->text()->setText("0");
        outputGroup->layout()->addWidget(textEpoch);

        auto textMSE = new TextField();
        textMSE->label()->setText("MSE均方根误差");
        textMSE->text()->setText("0");
        textMSE->text()->setReadOnly(true);
        outputGroup->layout()->addWidget(textMSE);

        auto textScore = m_textScore = new TextField();
        textScore->label()->setText("Total Score");
        textScore->text()->setText("0");
        textScore->text()->setReadOnly(true);
        outputGroup->layout()->addWidget(textScore);
    }

    this->layout()->addWidget(m_chartWidget);
    this->layout()->addWidget(groupBox);

    m_chartWidget->forecastSeries()->append(0.5,0.5);
    m_chartWidget->actualSeries()->append(0.6,0.6);
}

void GeneralModelView::setTotalScoreVisibility(bool value) {
    if (value)
        m_textScore->show();
    else
        m_textScore->hide();
}
