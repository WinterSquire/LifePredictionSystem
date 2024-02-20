#ifndef LIFEPREDICTIONSYSTEM_DEFAULTCHARTWIDGET_H
#define LIFEPREDICTIONSYSTEM_DEFAULTCHARTWIDGET_H

#include <QWidget>
#include <QScatterSeries>

class QChart;
class QChartView;

class DefaultChartWidget : public QWidget{
    Q_OBJECT
public:
    DefaultChartWidget(QWidget* parent = nullptr);

    QScatterSeries* forecastSeries() {return m_fSeries;}
    QScatterSeries* actualSeries() {return m_aSeries;}
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QChart* m_chart;
    QChartView* m_chartView;
    QScatterSeries* m_fSeries;
    QScatterSeries* m_aSeries;
};


#endif //LIFEPREDICTIONSYSTEM_DEFAULTCHARTWIDGET_H
