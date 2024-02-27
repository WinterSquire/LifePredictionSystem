#ifndef LIFEPREDICTIONSYSTEM_TEXTFIELD_H
#define LIFEPREDICTIONSYSTEM_TEXTFIELD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class TextField : public QWidget {
    Q_OBJECT
public:
    TextField(QWidget* parent = nullptr);

    QLabel* label() {return m_label;};
    QLineEdit* text() {return m_text;};

private:
    QLabel* m_label;
    QLineEdit* m_text;
};

#endif //LIFEPREDICTIONSYSTEM_TEXTFIELD_H
