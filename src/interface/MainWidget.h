#ifndef LIFEPREDICTIONSYSTEM_MAINWIDGET_H
#define LIFEPREDICTIONSYSTEM_MAINWIDGET_H

#include <QWidget>
#include <QHash>

class MainWidget : public QWidget {
    Q_OBJECT
public:
    MainWidget(QWidget* parent = nullptr);

    enum class eModel {
        MODEL_ANN,
        MODEL_KNN,
        MODEL_CNN,
        MODEL_PC
    };
protected:

private:
    void openModel(eModel model);


    const QMap<QString, eModel> m_modelMap;
};


#endif //LIFEPREDICTIONSYSTEM_MAINWIDGET_H
