#ifndef LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
#define LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H

#include <QWidget>

#include "DefaultChartWidget.h"

class TextField;

class GeneralModelView : public QWidget {
    Q_OBJECT
public:
    GeneralModelView(QWidget* parent = nullptr);

    void setTotalScoreVisibility(bool value);
protected:

private:
    DefaultChartWidget* m_chartWidget;
    TextField* m_textScore;
};


#endif //LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
