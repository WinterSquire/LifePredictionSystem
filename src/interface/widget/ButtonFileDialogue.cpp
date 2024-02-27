#include "ButtonFileDialogue.h"

#include <QFileDialog>

ButtonFileDialogue::ButtonFileDialogue(QWidget *parent)
        : QPushButton(parent) {
    setText("选择文件");
    connect(this, &QPushButton::clicked, this, &ButtonFileDialogue::selectFile);
}

void ButtonFileDialogue::selectFile() {
    auto result = QFileDialog::getOpenFileName(
            this,
            "选择数据文件",
            "",
            "Data Files(*.csv *.txt)"
            );

    if (!result.isEmpty()) {
        m_selectedFile = result;
    }
}

QString ButtonFileDialogue::selectedFile() const & {
    return m_selectedFile;
}
