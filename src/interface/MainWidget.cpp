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
    , m_list({
//        {"ANN预测", eModel::MODEL_ANN},
        {"CNN预测", eModel::MODEL_CNN},
        {"KNN预测", eModel::MODEL_KNN},
//        {"PlaceHolder", eModel::MODEL_PC},
    }), m_modelMap()
{
    auto layout = new QVBoxLayout();
    setLayout(layout);

    for (auto item: m_list) {
        m_modelMap.insert(item.first, item.second);

        auto button = new QPushButton(item.first, this);
        button->setStyleSheet("padding: 10px");

        layout->addWidget(button);

        connect(button, &QPushButton::pressed, this, [=](){
            openModel(m_modelMap[button->text()]);
        });
    }
}

#include "../python/PyWorker.h"
#include "../model/cnn/CNNParser.h"
#include "../model/knn/KNNParser.h"

void MainWidget::openModel(MainWidget::eModel model) {
    switch (model) {
        case eModel::MODEL_ANN:
            break;
        case eModel::MODEL_KNN:
            {
                auto view_KNN = new KNN(this);
                view_KNN->setFixedSize(1152, 648);
                view_KNN->setWindowTitle("KNN预测");
                view_KNN->show();
            }
            break;
        case eModel::MODEL_CNN:
            {
                auto view_CNN = new CNN(this);
                view_CNN->setFixedSize(1152, 648);
                view_CNN->show();
            }
            break;
        case eModel::MODEL_PC:
            break;
    }
}
