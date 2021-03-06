#include "resizehandle.h"
#include "sizegripdiagramitem.h"
#include "diagramitem.h"
#include "constants.h"
#include "internal.h"

#include <QGraphicsSceneHoverEvent>
#include <QGuiApplication>
#include <QCursor>
#include <QPainter>

ResizeHandle::ResizeHandle(PositionFlags positionFlags, SizeGrip *sizeGrip)
    : HandleItem(positionFlags, sizeGrip)
    , boundingRect_(-Constants::SizeHandleItem::OverralWidth  / 2,
                    -Constants::SizeHandleItem::OverralHeight / 2,
                     Constants::SizeHandleItem::OverralWidth,
                     Constants::SizeHandleItem::OverralHeight)

    , visibleRect_(-Constants::SizeHandleItem::VisibleWidth  / 2,
                   -Constants::SizeHandleItem::VisibleHeight / 2,
                    Constants::SizeHandleItem::VisibleWidth,
                    Constants::SizeHandleItem::VisibleHeight)
    , sizeGrip_(sizeGrip)
{
    Q_ASSERT(sizeGrip_);
    setFlag(ItemIsMovable);
    setCursorByFlag(positionFlags);
}

void ResizeHandle::setHandleManager(HandleManager *newHandleManager)
{
    sizeGrip_ = qobject_cast<SizeGrip*>(newHandleManager);
    Q_ASSERT(sizeGrip_);
    HandleItem::setHandleManager(sizeGrip_);
}

QRectF ResizeHandle::boundingRect() const
{
    return boundingRect_;
}

void ResizeHandle::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (shouldDraw()) {
        painter->setPen(QPen(Qt::darkGray));
        painter->setBrush(QBrush(Qt::white));
        painter->drawRect(visibleRect_);
    }
}

int ResizeHandle::type() const
{
    return Type;
}

void ResizeHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(sizeGrip_);

    QPointF pos = (event->pos());
    pos = internal::snapToGrid(pos, Constants::DiagramScene::GridSize);
    pos = restrictPosition(pos);

    QPointF mappedToScene = mapToScene(pos);
    pos = mapFromScene(internal::preventOutsideMove(mappedToScene, mappedToScene,
                                                    sizeGrip_->maxGripArea()));

    if ((pos) != (QGraphicsItem::pos()))
        changeParentBoundingRect(mapToParent(pos));
}

QPointF ResizeHandle::restrictPosition(const QPointF& newPos)
{
    QPointF retVal = pos();

    auto positionFlags = HandleItem::positionFlags();
    if (positionFlags & Top || positionFlags & Bottom)
        retVal.setY(newPos.y());

    if (positionFlags & Left || positionFlags & Right)
        retVal.setX(newPos.x());

    return retVal;
}

void ResizeHandle::changeParentBoundingRect(const QPointF &pos)
{
    Q_ASSERT(sizeGrip_);
    switch (HandleItem::positionFlags())
    {
    case TopLeft:
        sizeGrip_->setTopLeft(pos);
        break;
    case Top:
        sizeGrip_->setTop(pos.y());
        break;
    case TopRight:
        sizeGrip_->setTopRight(pos);
        break;
    case Right:
        sizeGrip_->setRight(pos.x());
        break;
    case BottomRight:
        sizeGrip_->setBottomRight(pos);
        break;
    case Bottom:
        sizeGrip_->setBottom(pos.y());
        break;
    case BottomLeft:
        sizeGrip_->setBottomLeft(pos);
        break;
    case Left:
        sizeGrip_->setLeft(pos.x());
        break;
    }
}

void ResizeHandle::setCursorByFlag(PositionFlags positionFlags)
{
    QCursor cursor;
    switch (positionFlags)
    {
    case TopLeft:
        cursor.setShape(Qt::SizeFDiagCursor);
        break;
    case Top:
        cursor.setShape(Qt::SizeVerCursor);
        break;
    case TopRight:
        cursor.setShape(Qt::SizeBDiagCursor);
        break;
    case Right:
        cursor.setShape(Qt::SizeHorCursor);
        break;
    case BottomLeft:
        cursor.setShape(Qt::SizeBDiagCursor);
        break;
    case Bottom:
        cursor.setShape(Qt::SizeVerCursor);
        break;
    case BottomRight:
        cursor.setShape(Qt::SizeFDiagCursor);
        break;
    case Left:
        cursor.setShape(Qt::SizeHorCursor);
        break;
    }
    setCursor(cursor);
}
