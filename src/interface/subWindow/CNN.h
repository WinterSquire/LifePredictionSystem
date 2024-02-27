#ifndef LIFEPREDICTIONSYSTEM_CNN_H
#define LIFEPREDICTIONSYSTEM_CNN_H

#include <QDialog>

#include "../widget/DefaultChartWidget.h"
#include "../widget/GeneralModelView.h"

class TextField;

class CNN : public GeneralModelView {
    Q_OBJECT
public:
    CNN(QWidget* parent = nullptr);

private slots:
    void startTask() override;
    void updateUI(const QString& result) override;

protected:

private:
    DefaultChartWidget *m_chartMSE, *m_chartLoss;
    QScatterSeries *m_aMSESeries, *m_fMSESeries;
    QScatterSeries *m_aLossSeries, *m_fLossSeries;
    TextField *m_textEpoch, *m_textMSE, *m_textScore;
};


#endif //LIFEPREDICTIONSYSTEM_CNN_H
