#include "DefaultChartWidget.h"

#include <QChart>
#include <QChartView>
#include <QScatterSeries>

DefaultChartWidget::DefaultChartWidget(QWidget* parent)
        : QWidget(parent)
        , m_chart(new QChart())
        , m_aSeries(new QScatterSeries())
        , m_fSeries(new QScatterSeries())
        , m_chartView(new QChartView(m_chart, this)) {
    // 设置散点的大小、颜色。
    m_aSeries->setName("实际值");
    m_aSeries->setMarkerSize(10);
    m_aSeries->setColor(QColor(Qt::green));
    m_aSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    m_fSeries->setName("预测值");
    m_fSeries->setMarkerSize(10);
    m_fSeries->setColor(QColor(Qt::yellow));
    m_fSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    // 设置图表
    m_chart->setTitle("散点图");
    m_chart->addSeries(m_aSeries);
    m_chart->addSeries(m_fSeries);
    m_chart->createDefaultAxes();
    m_chart->setAnimationOptions(QChart::AnimationOptions(QChart::AllAnimations));

    // 配置viewer
    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void DefaultChartWidget::resizeEvent(QResizeEvent *event) {
    m_chartView->resize(size());
}
