#ifndef SCREENDISPLAY_H
#define SCREENDISPLAY_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QKeyEvent>
#include "chip8.h"

class ScreenDisplay : public QGraphicsView
{
public:
    ScreenDisplay(CHIP8* chip8, QWidget* parent = nullptr);
    void updateDisplay(bool chip8_graphics[]);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    QGraphicsScene *scene {};
    QGraphicsRectItem *pixels [32*64] {};
    CHIP8* chip8;
};

#endif // SCREENDISPLAY_H
