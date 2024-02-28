#include "KNN.h"

#include <QLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QPlainTextEdit>

#include "../widget/TextField.h"
#include "../../model/knn/KNNParser.h"

KNN::KNN(QWidget* parent)
        : GeneralModelView(parent)
        , m_knnTypeComboBox(new QComboBox(this))
        , m_chartRMSE(new DefaultChartWidget(this))
        , m_chartScore(new DefaultChartWidget(this))
{
    this->setWindowTitle("KNN预测");
    this->setFixedSize(1152, 648);

    {
        m_chartRMSE->setChartTitle("RMSE");
        m_chartRMSE->setAxisXName("N-Neighbors");
        m_chartRMSE->setAxisYName("MSE");
        m_chartRMSE->setFixedSize(400, 400);

        m_fRMSESeries = m_chartRMSE->addSeries();

        m_fRMSESeries->setName("预测值");
        m_fRMSESeries->setMarkerSize(10);
        m_fRMSESeries->setColor(QColor(Qt::yellow));
        m_fRMSESeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    }

    {
        m_chartScore->setChartTitle("Total Score");
        m_chartScore->setAxisXName("N-Neighbors");
        m_chartScore->setAxisYName("Loss");
        m_chartScore->setFixedSize(400, 400);

        m_fScoreSeries = m_chartScore->addSeries();

        m_fScoreSeries->setName("预测值");
        m_fScoreSeries->setMarkerSize(10);
        m_fScoreSeries->setColor(QColor(Qt::yellow));
        m_fScoreSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    }

    this->setLayout(new QHBoxLayout());

    auto container_chart = new QWidget();
    container_chart->setLayout(new QHBoxLayout());
    this->layout()->addWidget(container_chart);

    container_chart->layout()->addWidget(m_chartRMSE);
    container_chart->layout()->addWidget(m_chartScore);

    auto groupBox = new QGroupBox();
    groupBox->setLayout(new QVBoxLayout());

    {
        QMap<eKNNType, QString> enumMap = {
                {Type1, "第一类"},
                {Type2, "第二类"},
                {Type3, "第三类"},
                {Type4, "第四类"}
        };

        for (eKNNType value : enumMap.keys()) {
            m_knnTypeComboBox->addItem(enumMap[value], QVariant(value));
        }

        m_knnTypeComboBox->setCurrentIndex(0);

        groupBox->layout()->addWidget(m_knnTypeComboBox);
    }

    // 设置按钮
    {
        auto buttonGroup = new QGroupBox();
        buttonGroup->setLayout(new QVBoxLayout());
        groupBox->layout()->addWidget(buttonGroup);

        buttonGroup->layout()->addWidget(m_btnSelectFile);
        buttonGroup->layout()->addWidget(m_btnExecute);
    }

    this->layout()->addWidget(m_chartRMSE);
    this->layout()->addWidget(groupBox);
}

void KNN::startTask() {
    auto selectedFile = m_btnSelectFile->selectedFile();

    if (!QFileInfo(selectedFile).exists()) {
        QMessageBox::warning(this, "警告", "数据文件无效", QMessageBox::Ok);
        return;
    }

    auto knn = PyTask{"ModelSet", "knn", {selectedFile.toStdString(), std::to_string(m_knnTypeComboBox->currentIndex())}};

    emit m_btnExecute->startTask(knn);
}

void updateChart(DefaultChartWidget *chart, QScatterSeries *series, const vector<double> &data_x, const vector<double> &data_y) {
    double range_maxx = 0;
    double range_miny = 0;
    double range_maxy = 10;

    series->clear();

    if (data_x.size() > 0) {
        range_maxx = data_x[0];

        range_miny = data_y[0];
        range_maxy = data_y[0];

        for (int i = 0; i < data_x.size(); ++i) {
            double sx = data_x[i];
            double sy = data_y[i];

            if (sy < range_miny) range_miny = sy;
            if (sy > range_maxy) range_maxy = sy;

            if (sx > range_maxx) range_maxx = sx;

            series->append(sx, sy);
        }
    }

    chart->setAxisXRange(0, range_maxx + 1);
    chart->setAxisYRange(range_miny >= 10 ? range_miny - 10 : range_miny,range_maxy + 10);
    chart->update();
}

void KNN::updateUI(const QString &result) {
    auto data = Model::KNN::Parse(result.toStdString().c_str());
    updateChart(m_chartRMSE, m_fRMSESeries, data.n_neighbors, data.rmse);
    updateChart(m_chartScore, m_fScoreSeries, data.n_neighbors, data.total_score);
}
