#ifndef NEWEXPERIMENTWINDOW_H
#define NEWEXPERIMENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewExperimentWindow;
}

class NewExperimentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewExperimentWindow(QWidget *parent = 0);
    ~NewExperimentWindow();

private:
    Ui::NewExperimentWindow *ui;
};

#endif // NEWEXPERIMENTWINDOW_H