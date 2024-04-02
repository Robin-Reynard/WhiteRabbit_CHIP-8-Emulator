#ifndef WHITERABBITMAINWINDOW_H
#define WHITERABBITMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WhiteRabbitMainWindow; }
QT_END_NAMESPACE

class WhiteRabbitMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    WhiteRabbitMainWindow(QWidget *parent = nullptr);
    ~WhiteRabbitMainWindow();

private:
    Ui::WhiteRabbitMainWindow *ui;
};
#endif // WHITERABBITMAINWINDOW_H
