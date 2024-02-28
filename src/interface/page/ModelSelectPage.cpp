#include "ModelSelectPage.h"

#include <QtCore>
#include <QLayout>
#include <QPushButton>
#include <QWidget>

#include "../subWindow/CNN.h"
#include "../subWindow/KNN.h"

ModelSelectPage::ModelSelectPage(QWidget* parent)
    : QWidget(parent)
    , m_modelMap({
//        {"ANN预测", eModel::MODEL_ANN},
        {"CNN预测", eModel::MODEL_CNN},
        {"KNN预测", eModel::MODEL_KNN},
//        {"PlaceHolder", eModel::MODEL_PC},
    })
{
    auto layout = new QVBoxLayout();
    setLayout(layout);

    for (auto item: m_modelMap.toStdMap()) {
        auto button = new QPushButton(item.first, this);
        button->setIcon(QIcon(":/icon/model_icon.png"));
        button->setStyleSheet("padding: 10px");
        layout->addWidget(button);

        connect(button, &QPushButton::pressed, this, [=](){
            openModel(item.second);
        });
    }
}

void ModelSelectPage::openModel(ModelSelectPage::eModel model) {
    if (m_currentModel) return;

    switch (model) {
        case eModel::MODEL_ANN:
            break;
        case eModel::MODEL_KNN:
            m_currentModel = new KNN(this);
            break;
        case eModel::MODEL_CNN:
            m_currentModel = new CNN(this);
            break;
        case eModel::MODEL_PC:
            break;
    }

    if (m_currentModel) {
        m_currentModel->show();
        connect(m_currentModel, &QObject::destroyed, this, &ModelSelectPage::onModelClosed);
    }
}

void ModelSelectPage::onModelClosed() {
    m_currentModel = nullptr;
}
