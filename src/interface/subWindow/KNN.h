#ifndef LIFEPREDICTIONSYSTEM_KNN_H
#define LIFEPREDICTIONSYSTEM_KNN_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>

#include "../widget/DefaultChartWidget.h"

#include "../../model/knn/KNNResult.h"

class TextField;

class KNN : public QDialog {
Q_OBJECT
public:
    enum eKNNType : int { Type1, Type2, Type3, Type4};
public:
    KNN(QWidget* parent = nullptr);

    void setData(const Model::KNN::Result& result);
protected:

private:
    QString selectedFile;
    QPushButton *m_btnExecute;
    DefaultChartWidget *m_chartRMSE, *m_chartScore;
    QScatterSeries *m_aRMSESeries, *m_fRMSESeries;
    QScatterSeries *m_aScoreSeries, *m_fScoreSeries;
    eKNNType m_knnType = Type1;
    QComboBox *m_knnTypeComboBox;
};


#endif //LIFEPREDICTIONSYSTEM_KNN_H
