#ifndef LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
#define LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H

#include <QDialog>

#include "./DefaultChartWidget.h"
#include "../widget/ButtonExecutor.h"
#include "../widget/ButtonFileDialogue.h"


class GeneralModelView : public QDialog {
    Q_OBJECT
public:
    using Range = DefaultChartWidget::Range;

    GeneralModelView(QWidget *parent = nullptr, const QString &title = "模型预测");

protected:
    ButtonFileDialogue *m_btnSelectFile;
    ButtonExecutor *m_btnExecute;

    void closeEvent(QCloseEvent *) override;

    Range GetRange(const vector<vector<double>> &data);
    bool SetSeriesData(QScatterSeries *series, const vector<double> &data_x, const vector<double> &data_y);
protected slots:
    virtual void startTask() = 0;
    virtual void updateUI(const QString& result) = 0;
};


#endif //LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
