#include "sizegrip.h"
#include "resizehandle.h"
#include "diagramitem.h"

#include "constants.h"
#include "internal.h"

#include <QDebug>

SizeGrip::SizeGrip(QGraphicsItem *item, const QRectF &resizeRect, const QSizeF &minGripSize, QObject *parent)
    : HandleManager(item, parent)
    , resizeRect_(resizeRect)
    , minGripSize_(minGripSize)
{
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::TopLeft    , this));
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::Top        , this));
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::TopRight   , this));
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::Left       , this));
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::Right      , this));
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::BottomLeft , this));
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::Bottom     , this));
    HandleManager::addHandleItem(new ResizeHandle(PositionFlags::BottomRight, this));

    updateHandleItemsPositions();
    setShouldDrawForHandleItems(false);
}

void SizeGrip::setTop(qreal y)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setTop(y);
    if (resizeRect_.height() < minGripSize_.height()) {
        resizeRect_ = oldRect;
        return;
    }
    doResize();
}

void SizeGrip::setRight(qreal x)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setRight(x);
    if (resizeRect_.width() < minGripSize_.width()) {
        resizeRect_ = oldRect;
        return;
    }
    doResize();
}

void SizeGrip::setBottom(qreal y)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setBottom(y);
    if (resizeRect_.height() < minGripSize_.height()) {
        resizeRect_ = oldRect;
        return;
    }
    doResize();
}

void SizeGrip::setLeft(qreal v)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setLeft(v);
    if (resizeRect_.width() < minGripSize_.width()) {
        resizeRect_ = oldRect;
        return;
    }
    doResize();
}

void SizeGrip::setTopLeft(const QPointF &pos)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setTopLeft(pos);

    if (resizeRect_.width() < minGripSize_.width())
        resizeRect_.setLeft(oldRect.left());

    if (resizeRect_.height() < minGripSize_.height())
        resizeRect_.setTop(oldRect.top());

    if (resizeRect_ != oldRect)
        doResize();
}

void SizeGrip::setTopRight(const QPointF &pos)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setTopRight(pos);

    if (resizeRect_.width() < minGripSize_.width())
        resizeRect_.setRight(oldRect.right());

    if (resizeRect_.height() < minGripSize_.height())
        resizeRect_.setTop(oldRect.top());

    if (resizeRect_ != oldRect)
        doResize();
}

void SizeGrip::setBottomRight(const QPointF &pos)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setBottomRight(pos);

    if (resizeRect_.width() < minGripSize_.width())
        resizeRect_.setRight(oldRect.right());

    if (resizeRect_.height() < minGripSize_.height())
        resizeRect_.setBottom(oldRect.bottom());

    if (resizeRect_ != oldRect)
        doResize();
}

void SizeGrip::setBottomLeft(const QPointF &pos)
{
    QRectF oldRect = resizeRect_;
    resizeRect_.setBottomLeft(pos);

    if (resizeRect_.width() < minGripSize_.width())
        resizeRect_.setLeft(oldRect.left());

    if (resizeRect_.height() < minGripSize_.height())
        resizeRect_.setBottom(oldRect.bottom());

    if (resizeRect_ != oldRect)
        doResize();
}

void SizeGrip::resize(const QRectF &rect)
{
    resizeRect_ = rect;
    doResize();
}

void SizeGrip::doResize()
{
    emit getReadyToResize();
    resizeLogic();
    emit resizeBeenMade();
    updateHandleItemsPositions();
}

void SizeGrip::updateHandleItemsPositions()
{
    for (auto sizeHandle : qAsConst(HandleManager::handleItems())) {

        switch (sizeHandle->positionFlags())
        {
        case PositionFlags::TopLeft:
            sizeHandle->setPos(resizeRect_.topLeft());
            break;
        case PositionFlags::Top:
            sizeHandle->setPos(resizeRect_.left() + resizeRect_.width() / 2,
                         resizeRect_.top());
            break;
        case PositionFlags::TopRight:
            sizeHandle->setPos(resizeRect_.topRight());
            break;
        case PositionFlags::Right:
            sizeHandle->setPos(resizeRect_.right(),
                         resizeRect_.top() + resizeRect_.height() / 2);
            break;
        case PositionFlags::BottomRight:
            sizeHandle->setPos(resizeRect_.bottomRight());
            break;
        case PositionFlags::Bottom:
            sizeHandle->setPos(resizeRect_.left() + resizeRect_.width() / 2,
                         resizeRect_.bottom());
            break;
        case PositionFlags::BottomLeft:
            sizeHandle->setPos(resizeRect_.bottomLeft());
            break;
        case PositionFlags::Left:
            sizeHandle->setPos(resizeRect_.left(),
                         resizeRect_.top() + resizeRect_.height() / 2);
            break;
        }

    }
}

const QSizeF &SizeGrip::minGripSize() const
{
    return minGripSize_;
}

void SizeGrip::setMinGripSize(const QSizeF &newMinGripSize)
{
    minGripSize_ = newMinGripSize;
}

const QRectF &SizeGrip::maxGripArea() const
{
    return maxGripArea_;
}

void SizeGrip::setMaxGripArea(const QRectF &newMaxGripArea)
{
    maxGripArea_ = newMaxGripArea;
}

const QRectF &SizeGrip::resizeRect() const
{
    return resizeRect_;
}

void SizeGrip::setResizeRect(const QRectF &newRect)
{
    resizeRect_ = newRect;
}
