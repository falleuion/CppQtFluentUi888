#include "FluScrollDelegate.h"
#include "FluScrollArea.h"
#include "FluScrollBar.h"
#include <QAbstractItemView>

FluScrollDelegate::FluScrollDelegate(FluScrollArea* scrollArea /*= nullptr*/) : QObject(scrollArea)
{
    m_scrollArea = scrollArea;
    m_vScrollBar = new FluScrollBar(Qt::Vertical, scrollArea);
    m_hScrollBar = new FluScrollBar(Qt::Horizontal, scrollArea);

    auto itemView = qobject_cast<QAbstractItemView*>(scrollArea);
    if (itemView != nullptr)
    {
        itemView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        itemView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    }

    m_scrollArea->viewport()->installEventFilter(this);
}

bool FluScrollDelegate::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent* wheelEvent = (QWheelEvent*)(event);
        if (wheelEvent->angleDelta().y() != 0)
        {
            m_vScrollBar->scrollCurrentValue(-wheelEvent->angleDelta().y());
        }
        else
        {
            m_hScrollBar->scrollCurrentValue(-wheelEvent->angleDelta().x());
        }
        event->setAccepted(true);
        return true;
    }

    return QObject::eventFilter(watched, event);
}