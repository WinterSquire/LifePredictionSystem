#ifndef LIFEPREDICTIONSYSTEM_DEFAULTCHARTWIDGET_H
#define LIFEPREDICTIONSYSTEM_DEFAULTCHARTWIDGET_H

#include <QWidget>
#include <QScatterSeries>
#include <QValueAxis>
#include <QChartView>

class QChart;

class DefaultChartWidget : public QWidget{
    Q_OBJECT
public:
    DefaultChartWidget(QWidget* parent = nullptr);

    QScatterSeries* forecastSeries() {return m_fSeries;}
    QScatterSeries* actualSeries() {return m_aSeries;}
    void update();
    void setAxisXRange(double min, double max);
    void setAxisYRange(double min, double max);
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QChart* m_chart;
    QChartView* m_chartView;
    QScatterSeries* m_fSeries;
    QScatterSeries* m_aSeries;
    QValueAxis* m_axisX;
    QValueAxis* m_axisY;
};


#endif //LIFEPREDICTIONSYSTEM_DEFAULTCHARTWIDGET_H
