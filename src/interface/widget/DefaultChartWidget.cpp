#include "DefaultChartWidget.h"

#include <QChart>
#include <QChartView>
#include <QScatterSeries>

DefaultChartWidget::DefaultChartWidget(QWidget* parent)
        : QWidget(parent)
        , m_chart(new QChart())
        , m_axisX(new QValueAxis())
        , m_axisY(new QValueAxis())
        , m_chartView(new QChartView(this)) {

    // 设置图表
    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_chart->createDefaultAxes();
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

QScatterSeries *DefaultChartWidget::addSeries() {
    auto result = new QScatterSeries();
    m_chart->addSeries(result);
    result->attachAxis(m_axisX);
    result->attachAxis(m_axisY);
    return result;
}

void DefaultChartWidget::setAxisXName(const char *name) {
    m_axisX->setTitleText(name);
}

void DefaultChartWidget::setAxisYName(const char *name) {
    m_axisY->setTitleText(name);
}

void DefaultChartWidget::setChartTitle(const char *title) {
    m_chart->setTitle(title);
}
