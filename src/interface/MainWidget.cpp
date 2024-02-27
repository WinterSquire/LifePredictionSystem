#include "MainWidget.h"

#include <QDialog>
#include <QtCore>
#include <QLayout>
#include <QPushButton>
#include <QWidget>

#include "subWindow/CNN.h"
#include "subWindow/KNN.h"

MainWidget::MainWidget(QWidget* parent)
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
        button->setStyleSheet("padding: 10px");
        layout->addWidget(button);

        connect(button, &QPushButton::pressed, this, [=](){
            openModel(item.second);
        });
    }
}

#include "../python/PyWorker.h"

void MainWidget::openModel(MainWidget::eModel model) {
    switch (model) {
        case eModel::MODEL_ANN:
            break;
        case eModel::MODEL_KNN:
            (new KNN(this))->show();
            break;
        case eModel::MODEL_CNN:
            (new CNN(this))->show();
            break;
        case eModel::MODEL_PC:
            break;
    }
}
