#ifndef LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
#define LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H

#include <QDialog>

#include "../widget/ButtonExecutor.h"
#include "../widget/ButtonFileDialogue.h"


class GeneralModelView : public QDialog {
    Q_OBJECT
public:
    GeneralModelView(QWidget* parent = nullptr);

protected:
    ButtonFileDialogue *m_btnSelectFile;
    ButtonExecutor *m_btnExecute;

protected slots:
    virtual void startTask() = 0;
    virtual void updateUI(const QString& result) = 0;
};


#endif //LIFEPREDICTIONSYSTEM_GENERALMODELVIEW_H
