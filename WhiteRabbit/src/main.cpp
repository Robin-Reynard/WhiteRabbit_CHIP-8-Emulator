#include <QApplication>
#include "dualwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DualWindow w;
    w.show();

    while(w.isVisible()){
        a.processEvents();
        w.emulate_next_instruction();
    }
}
