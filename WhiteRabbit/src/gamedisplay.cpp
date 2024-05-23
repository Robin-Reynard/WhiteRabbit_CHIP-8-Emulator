#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>

class GameDisplay : public QGraphicsView {
public:
    GameDisplay(QWidget* parent = nullptr) : QGraphicsView(parent) {
        QGraphicsScene* scene = new QGraphicsScene(this);
        setScene(scene);

        // Set the size of the board
        int boardSize = 8; // 8x8 board
        int cellSize = 50; // Size of each cell

        // Create the board
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                // Alternate colors for cells
                QColor color = (i + j) % 2 == 0 ? Qt::lightGray : Qt::darkGray;
                QBrush brush(color);
                QPen pen(Qt::black);

                // Create rectangle representing a cell
                QGraphicsRectItem* cell = scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize, pen, brush);
            }
        }

        // Set the scene rect to ensure all cells are visible
        scene->setSceneRect(0, 0, boardSize * cellSize, boardSize * cellSize);

        // Adjust view
        setFixedSize(boardSize * cellSize + 2, boardSize * cellSize + 2); // +2 to account for border
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
};
