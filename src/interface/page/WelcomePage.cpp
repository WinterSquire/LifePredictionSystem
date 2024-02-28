#include "WelcomePage.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

WelcomePage::WelcomePage(QWidget* parent) : QWidget(parent) {
    setLayout(new QVBoxLayout());
    layout()->setAlignment(Qt::AlignCenter);
    layout()->setSpacing(40);

    // label
    auto label = new QLabel("机械寿命预测系统", this);
    label->setStyleSheet("font-size: 20px; font-weight: bold;");
    label->setAlignment(Qt::AlignCenter);

    auto button = new QPushButton("进入系统", this);
    button->setStyleSheet("font-size: 16px;");
    button->setFixedWidth(200);
    connect(button, &QPushButton::pressed, this, [=](){
        emit onBtnStartClicked(ePage::MODEL_SELECT);
    });

    layout()->addWidget(label);
    layout()->addWidget(button);
}