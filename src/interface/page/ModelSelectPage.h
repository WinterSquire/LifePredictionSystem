#ifndef LIFEPREDICTIONSYSTEM_MODELSELECTPAGE_H
#define LIFEPREDICTIONSYSTEM_MODELSELECTPAGE_H

#include <QWidget>
#include <QHash>

#include "../widget/GeneralModelView.h"

class ModelSelectPage : public QWidget {
    Q_OBJECT
public:
    ModelSelectPage(QWidget* parent = nullptr);

    enum class eModel {
        MODEL_ANN,
        MODEL_KNN,
        MODEL_CNN,
        MODEL_PC
    };
protected:

private:
    void openModel(eModel model);
    void onModelClosed();

    const QMap<QString, eModel> m_modelMap;
    GeneralModelView* m_currentModel = nullptr;
};


#endif //LIFEPREDICTIONSYSTEM_MODELSELECTPAGE_H
