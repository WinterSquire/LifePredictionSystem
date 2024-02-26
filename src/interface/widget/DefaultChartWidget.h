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

    QScatterSeries* addSeries();
    void update();
    void setChartTitle(const char *title);
    void setAxisXRange(double min, double max);
    void setAxisXName(const char *name);
    void setAxisYRange(double min, double max);
    void setAxisYName(const char *name);
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QChart* m_chart;
    QChartView* m_chartView;
    QValueAxis* m_axisX;
    QValueAxis* m_axisY;
};


#endif //LIFEPREDICTIONSYSTEM_DEFAULTCHARTWIDGET_H
