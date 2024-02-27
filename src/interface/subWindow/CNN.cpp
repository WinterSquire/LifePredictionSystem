#include "CNN.h"

#include <QFileInfo>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QMessageBox>

#include "../widget/TextField.h"
#include "../../model/cnn/CNNParser.h"

CNN::CNN(QWidget* parent)
    : GeneralModelView(parent)
    , m_chartMSE(new DefaultChartWidget(this))
    , m_chartLoss(new DefaultChartWidget(this))
{
    this->setWindowTitle("CNN预测");
    this->setFixedSize(1152, 648);

    {
        m_chartMSE->setChartTitle("MSE");
        m_chartMSE->setAxisXName("Epoch");
        m_chartMSE->setAxisYName("MSE");
        m_chartMSE->setFixedSize(400, 400);

        m_aMSESeries = m_chartMSE->addSeries();
        m_fMSESeries = m_chartMSE->addSeries();

        // 设置散点的大小、颜色。
        m_aMSESeries->setName("实际值");
        m_aMSESeries->setMarkerSize(10);
        m_aMSESeries->setColor(QColor(Qt::green));
        m_aMSESeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

        m_fMSESeries->setName("预测值");
        m_fMSESeries->setMarkerSize(10);
        m_fMSESeries->setColor(QColor(Qt::yellow));
        m_fMSESeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    }

    {
        m_chartLoss->setChartTitle("Loss");
        m_chartLoss->setAxisXName("Epoch");
        m_chartLoss->setAxisYName("Loss");
        m_chartLoss->setFixedSize(400, 400);

        m_aLossSeries = m_chartLoss->addSeries();
        m_fLossSeries = m_chartLoss->addSeries();

        m_aLossSeries->setName("实际值");
        m_aLossSeries->setMarkerSize(10);
        m_aLossSeries->setColor(QColor(Qt::green));
        m_aLossSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

        m_fLossSeries->setName("预测值");
        m_fLossSeries->setMarkerSize(10);
        m_fLossSeries->setColor(QColor(Qt::yellow));
        m_fLossSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    }

    this->setLayout(new QHBoxLayout());

    auto container_chart = new QWidget();
    container_chart->setLayout(new QHBoxLayout());
    this->layout()->addWidget(container_chart);

    container_chart->layout()->addWidget(m_chartMSE);
    container_chart->layout()->addWidget(m_chartLoss);

    auto groupBox = new QGroupBox();
    groupBox->setLayout(new QVBoxLayout());

    // 设置按钮
    {
        auto buttonGroup = new QGroupBox();
        buttonGroup->setLayout(new QVBoxLayout());
        groupBox->layout()->addWidget(buttonGroup);

        buttonGroup->layout()->addWidget(m_btnSelectFile);
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

    this->layout()->addWidget(m_chartMSE);
    this->layout()->addWidget(groupBox);
}

void updateChart(DefaultChartWidget *chart, QScatterSeries *aSeries, QScatterSeries *fSeries
    , const vector<double> &actual, const vector<double> &forecast) {

    int epoch = actual.size();
    double range_miny = 0;
    double range_maxy = 10;

    aSeries->clear();
    fSeries->clear();

    if (epoch > 0) {
        range_miny = actual[0];
        range_maxy = actual[0];

        for (int i = 0; i < epoch; ++i) {
            double sy = actual[i];
            double fy = forecast[i];

            if (sy < range_miny) range_miny = sy;
            if (sy > range_maxy) range_maxy = sy;

            aSeries->append(i + 1, sy);
            fSeries->append(i + 1, fy);
        }
    }

    chart->setAxisXRange(0, epoch);
    chart->setAxisYRange(range_miny >= 1000 ? range_miny - 1000 : range_miny,range_maxy + 1000);
    chart->update();
}

void CNN::startTask() {
    auto selectedFile = m_btnSelectFile->selectedFile();

    if (!QFileInfo(selectedFile).exists()) {
        QMessageBox::warning(this, "警告", "数据文件无效", QMessageBox::Ok);
        return;
    }

    auto cnn = PyTask{"ModelSet", "cnn", {selectedFile.toStdString()}};

    emit m_btnExecute->startTask(cnn);
}

void CNN::updateUI(const QString& result) {
    auto data = Model::CNN::Parse(result.toStdString().c_str());

    updateChart(m_chartMSE, m_aMSESeries, m_fMSESeries, data.sel.mse, data.val.mse);
    updateChart(m_chartLoss, m_aLossSeries, m_fLossSeries, data.sel.loss, data.val.loss);

    m_textEpoch->text()->setText(QString::number(data.sel.mse.size()));
    m_textMSE->text()->setText(QString::number(data.mean_mse));
    m_textScore->text()->setText(QString::number(data.total_score));
}
