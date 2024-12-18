#ifndef DUALWINDOW_H
#define DUALWINDOW_H

#include <QMainWindow>

namespace Ui {
class DualWindow;
}

class DualWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DualWindow(QWidget *parent = nullptr);
    ~DualWindow();

private:
    Ui::DualWindow *ui;
};

#endif // DUALWINDOW_H
