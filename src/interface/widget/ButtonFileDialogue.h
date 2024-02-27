#ifndef LIFEPREDICTIONSYSTEM_BUTTONFILEDIALOGUE_H
#define LIFEPREDICTIONSYSTEM_BUTTONFILEDIALOGUE_H

#include <QPushButton>

class ButtonFileDialogue : public QPushButton {
    Q_OBJECT
public:
    ButtonFileDialogue(QWidget *parent = nullptr);

    QString selectedFile() const &;
private:
    void selectFile();

    QString m_selectedFile;
};


#endif //LIFEPREDICTIONSYSTEM_BUTTONFILEDIALOGUE_H
