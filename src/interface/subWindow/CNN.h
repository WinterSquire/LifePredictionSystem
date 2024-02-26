#ifndef LIFEPREDICTIONSYSTEM_CNN_H
#define LIFEPREDICTIONSYSTEM_CNN_H

#include <QDialog>
#include <QPushButton>

#include "../widget/DefaultChartWidget.h"

#include "../../model/cnn/CNNResult.h"

class TextField;

class CNN : public QDialog {
    Q_OBJECT
public:
    CNN(QWidget* parent = nullptr);

    void setData(const Model::CNN::Result& result);
    QPushButton* btnExecute() {return m_btnExecute;}
protected:

private:
    QString selectedFile;
    QPushButton *m_btnExecute;
    DefaultChartWidget *m_chartMSE, *m_chartLoss;
    QScatterSeries *m_aMSESeries, *m_fMSESeries;
    QScatterSeries *m_aLossSeries, *m_fLossSeries;
    TextField *m_textEpoch, *m_textMSE, *m_textScore;
};


#endif //LIFEPREDICTIONSYSTEM_CNN_H
