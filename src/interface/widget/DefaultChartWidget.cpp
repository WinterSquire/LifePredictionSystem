#include "DefaultChartWidget.h"

#include <QChart>
#include <QChartView>
#include <QScatterSeries>

DefaultChartWidget::DefaultChartWidget(QWidget* parent)
        : QWidget(parent)
        , m_chart(new QChart())
        , m_aSeries(new QScatterSeries())
        , m_fSeries(new QScatterSeries())
        , m_axisX(new QValueAxis())
        , m_axisY(new QValueAxis())
        , m_chartView(new QChartView(this)) {

    // 设置图表
    m_chart->setTitle("散点图");
    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);
    m_chart->addSeries(m_aSeries);
    m_chart->addSeries(m_fSeries);

    // 设置散点的大小、颜色。
    m_aSeries->setName("实际值");
    m_aSeries->setMarkerSize(10);
    m_aSeries->attachAxis(m_axisX);
    m_aSeries->attachAxis(m_axisY);
    m_aSeries->setColor(QColor(Qt::green));
    m_aSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    m_fSeries->setName("预测值");
    m_fSeries->setMarkerSize(10);
    m_fSeries->attachAxis(m_axisX);
    m_fSeries->attachAxis(m_axisY);
    m_fSeries->setColor(QColor(Qt::yellow));
    m_fSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    m_chart->createDefaultAxes();
    m_chart->axisX()->setTitleText("Epoch");
    m_chart->axisY()->setTitleText("MSE");
    m_chart->setAnimationOptions(QChart::AnimationOptions(QChart::AllAnimations));

    // 配置viewer
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setChart(m_chart);
}

void DefaultChartWidget::resizeEvent(QResizeEvent *event) {
    m_chartView->resize(size());
}

void DefaultChartWidget::update() {
    m_chartView->update();
}

void DefaultChartWidget::setAxisXRange(double min, double max) {
    m_chart->axisX()->setRange(min, max);
//    if (m_axisX) m_axisX->rangeChanged(min, max); // crash
}

void DefaultChartWidget::setAxisYRange(double min, double max) {
    m_chart->axisY()->setRange(min, max);
//    if (m_axisY) m_axisY->rangeChanged(min, max); //crash
}
