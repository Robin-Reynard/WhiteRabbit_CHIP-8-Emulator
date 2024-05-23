#ifndef SCREENDISPLAY_H
#define SCREENDISPLAY_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class ScreenDisplay : public QGraphicsView
{
public:
    ScreenDisplay(QWidget* parent = nullptr);
    void updateDisplay(unsigned char chip8_graphics[]);
private:
    QGraphicsScene *scene {};
    QGraphicsRectItem *pixels [32*64] {};
};

#endif // SCREENDISPLAY_H
