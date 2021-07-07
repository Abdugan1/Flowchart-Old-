#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>

class DiagramItem;
class GraphicsItemGroup;

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum DefaultSize {
        Width = 645,
        Height = 975
    };

    enum {
        GridSize = 20
    };

public:
    DiagramScene(QObject* parent = nullptr);
    QPointF preventOutsideMove(QPointF topLeft, QGraphicsItem* item);
    QPointF preventOutsideMove(QPointF topLeft, QPointF bottomRight);

public slots:
    void onItemPositionChanged(const QPointF& pos);
    void onItemReleased();
    void selectAllItems();
    void destroyGraphicsItemGroup();
    void makeGroupOfSelectedItems();
    void deleteSelectedItems();


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    void deleteAllLines();
    void drawLevelLine(const QLineF& line);
    QPoint getItemCenter(const DiagramItem* item);
    void createGraphicsItemGroup(QList<DiagramItem*>& diagramItems);

private:
    GraphicsItemGroup* group_ = nullptr;

};

#endif // DIAGRAMSCENE_H
