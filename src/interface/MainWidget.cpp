#include "MainWidget.h"

#include <QtCore>
#include <QLayout>
#include <QPushButton>
#include <QWidget>

#include "./widget/GeneralModelView.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
    , m_list({
        {"ANN预测", eModel::MODEL_ANN},
        {"CNN预测", eModel::MODEL_CNN},
        {"KNN预测", eModel::MODEL_KNN},
        {"PlaceHolder", eModel::MODEL_PC},
    }), m_modelMap()
{
    setFixedSize(256, 512);
    // 设置窗口标题
    setWindowTitle("机器寿命预测系统");

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

void MainWidget::openModel(MainWidget::eModel model) {
    auto view = new GeneralModelView();
    view->setFixedSize(640, 480);

    switch (model) {
        case eModel::MODEL_ANN:
            view->setWindowTitle("ANN预测");
            view->setTotalScoreVisibility(false);
            break;
        case eModel::MODEL_KNN:
            view->setWindowTitle("KNN预测");
            view->setTotalScoreVisibility(false);
            break;
        case eModel::MODEL_CNN:
            view->setWindowTitle("CNN预测");
            view->setTotalScoreVisibility(true);
            connect(view->btnExecute(), &QPushButton::pressed, [=]{
                auto cnn = PyTask{"ModelSet", "cnn", {"./script/data/test.txt"}};

                PyWorker::RunPyScriptAsync(cnn, [=](string data) {
                    auto result = Model::CNN::Parse(data.c_str());
                    view->setData(result);
                });
            });
            break;
        case eModel::MODEL_PC:
            view->setWindowTitle("???预测");
            view->setTotalScoreVisibility(false);
            break;
    }

    view->show();
}
