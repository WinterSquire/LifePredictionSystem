#include "KNN.h"

#include <QLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QPlainTextEdit>

#include "../widget/TextField.h"
#include "../../python/PyTask.h"
#include "../../python/PyWorker.h"
#include "../../model/knn/KNNParser.h"

KNN::KNN(QWidget* parent)
        : QDialog(parent)
        , m_knnTypeComboBox(new QComboBox(this))
        , m_chartRMSE(new DefaultChartWidget(this))
        , m_chartScore(new DefaultChartWidget(this))
{
    {
        m_chartRMSE->setChartTitle("RMSE");
        m_chartRMSE->setAxisXName("N-Neighbors");
        m_chartRMSE->setAxisYName("MSE");
        m_chartRMSE->setFixedSize(400, 400);

        m_aRMSESeries = m_chartRMSE->addSeries();
        m_fRMSESeries = m_chartRMSE->addSeries();

        // 设置散点的大小、颜色。
        m_aRMSESeries->setName("实际值");
        m_aRMSESeries->setMarkerSize(10);
        m_aRMSESeries->setColor(QColor(Qt::green));
        m_aRMSESeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

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

        m_aScoreSeries = m_chartScore->addSeries();
        m_fScoreSeries = m_chartScore->addSeries();

        m_aScoreSeries->setName("实际值");
        m_aScoreSeries->setMarkerSize(10);
        m_aScoreSeries->setColor(QColor(Qt::green));
        m_aScoreSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

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
                {Type1, "Type1"},
                {Type2, "Type2"},
                {Type3, "Type3"},
                {Type4, "Type4"}
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

        auto btnSelectFile = new QPushButton("选择文件");
        connect(btnSelectFile, &QPushButton::pressed, [=]{
            auto dialogue = new QFileDialog(this);
            dialogue->setNameFilter("Data Files(*.csv *.txt)");
            if (dialogue->exec())
                selectedFile = dialogue->selectedFiles()[0];
        });

        m_btnExecute = new QPushButton("执行");
        connect(m_btnExecute, &QPushButton::pressed, [&]{
            if (!QFileInfo(selectedFile).exists()) {
                QMessageBox::warning(this, "警告", "数据文件无效", QMessageBox::Ok);
                return;
            }

            auto knn = PyTask{"ModelSet", "knn", {selectedFile.toStdString(), std::to_string(m_knnTypeComboBox->currentIndex())}};

            PyWorker::RunPyScriptAsync(knn, [=](string data) {
                auto result = Model::KNN::Parse(data.c_str());
                setData(result);
            });
        });

        buttonGroup->layout()->addWidget(btnSelectFile);
        buttonGroup->layout()->addWidget(m_btnExecute);
    }

    this->layout()->addWidget(m_chartRMSE);
    this->layout()->addWidget(groupBox);
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

void KNN::setData(const Model::KNN::Result &result) {
    updateChart(m_chartRMSE, m_fRMSESeries, result.n_neighbors, result.rmse);
    updateChart(m_chartScore, m_fScoreSeries, result.n_neighbors, result.total_score);
}
