#ifndef LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
#define LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H

#include <QWidget>
#include <QPushButton>

#include "DefaultChartWidget.h"

#include "../../model/ModelResult.h"

class TextField;

class GeneralModelView : public QWidget {
    Q_OBJECT
public:
    GeneralModelView(QWidget* parent = nullptr);

    void setTotalScoreVisibility(bool value);
    void setData(const Model::Result& result);
    QPushButton* btnExecute() {return m_btnExecute;}
protected:

private:
    QPushButton *m_btnExecute;
    DefaultChartWidget *m_chartWidget;
    TextField *m_textEpoch, *m_textMSE, *m_textScore;
};


#endif //LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
