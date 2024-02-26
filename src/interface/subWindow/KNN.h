#ifndef LIFEPREDICTIONSYSTEM_KNN_H
#define LIFEPREDICTIONSYSTEM_KNN_H

#include <QDialog>
#include <QPushButton>

#include "../widget/DefaultChartWidget.h"

#include "../../model/knn/KNNResult.h"

class TextField;

class KNN : public QDialog {
Q_OBJECT
public:
    KNN(QWidget* parent = nullptr);

    void setData(const Model::KNN::Result& result);
protected:

private:
    QPushButton *m_btnExecute;
    DefaultChartWidget *m_chartRMSE, *m_chartScore;
    QScatterSeries *m_aRMSESeries, *m_fRMSESeries;
    QScatterSeries *m_aScoreSeries, *m_fScoreSeries;
};


#endif //LIFEPREDICTIONSYSTEM_KNN_H
