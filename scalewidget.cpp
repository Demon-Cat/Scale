#include "scalewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtDebug>

ScaleWidget::ScaleWidget(QWidget *parent) : QWidget(parent)
{

}

void ScaleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#80FF0000"));
    painter.drawRect(rect());

    painter.save();
    painter.setPen(QPen(QColor("#FFFFFF"), 1));
    for (int x = 0; x < width(); x += 10)
    {
        painter.drawLine(QPoint(x, 0), QPoint(x, height()));
    }
    painter.restore();
}

void ScaleWidget::mousePressEvent(QMouseEvent *event)
{
    m_pressDistance = event->globalPos() - pos();
}

void ScaleWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void ScaleWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->globalPos() - m_pressDistance;
    if (p.x() > 0)
    {
        p.setX(0);
    }
    if (p.y() > 0)
    {
        p.setY(0);
    }
    if (p.x() + width() < parentWidget()->width())
    {
        p.setX(parentWidget()->width() - width());
    }
    if (p.y() + height() < parentWidget()->height())
    {
        p.setY(parentWidget()->height() - height());
    }
    move(p);
}

void ScaleWidget::wheelEvent(QWheelEvent *event)
{
    QPoint mousePoint = event->pos();
    QPoint numDegrees = event->angleDelta();
    if (!numDegrees.isNull())
    {
        qDebug() << numDegrees.y();
        if (numDegrees.y() > 0)
        {
            if (m_zoom < 1000)
            {
                m_zoom += 25;
            }
        }
        else
        {
            if (m_zoom > 100)
            {
                m_zoom -= 25;
            }
        }
    }
    qreal lastScale = m_scale;
    m_scale = m_zoom / 100.0;

    if (lastScale == m_scale)
    {
        return;
    }

    QPoint p = mapToParent(mousePoint);
    QTransform transform;
    transform.translate(p.x(), p.y());
    transform.scale(m_scale / lastScale, m_scale / lastScale);
    transform.translate(-p.x(), -p.y());
    QRect previousRc = geometry();
    QRect nextRc = transform.mapRect(previousRc);

    setGeometry(nextRc);
}
