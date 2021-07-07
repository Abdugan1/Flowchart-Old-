#include "graphicsitemgroup.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QCursor>
#include <QDebug>

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItem *parent)
    : QGraphicsItemGroup(parent)
{
    setAcceptHoverEvents(true);
}

QRectF GraphicsItemGroup::boundingRect() const
{
    QRectF rect = QGraphicsItemGroup::boundingRect();
    rect.setX(rect.x() - 15);
    rect.setY(rect.y() - 15);
    rect.setWidth(rect.width()   + 15);
    rect.setHeight(rect.height() + 15);
    return rect;
}

void GraphicsItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::darkCyan));
    painter->drawRect(boundingRect());
}

QVariant GraphicsItemGroup::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedHasChanged) {
        bool selected = value.toBool();
        if (!selected)
            emit lostSelection();
    }
    return QGraphicsItemGroup::itemChange(change, value);
}

void GraphicsItemGroup::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!QGuiApplication::overrideCursor())
        QGuiApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));

    QGraphicsItemGroup::hoverMoveEvent(event);
}

void GraphicsItemGroup::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGuiApplication::restoreOverrideCursor();
    QGraphicsItemGroup::hoverLeaveEvent(event);
}

void GraphicsItemGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGuiApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
    QGraphicsItemGroup::mousePressEvent(event);
}

void GraphicsItemGroup::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGuiApplication::restoreOverrideCursor();
    QGraphicsItemGroup::mouseReleaseEvent(event);
}