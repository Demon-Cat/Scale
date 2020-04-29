#include "scalewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

ScaleWidget::ScaleWidget(QWidget *parent) : QWidget(parent)
{

}

void ScaleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#80FF0000"));
    painter.drawRect(rect());
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
    move(event->globalPos() - m_pressDistance);
}

void ScaleWidget::wheelEvent(QWheelEvent *event)
{
    QPoint mousePoint = event->pos();
    QPoint numDegrees = event->angleDelta();
    if (!numDegrees.isNull())
    {
        if (numDegrees.y() < 0)
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
    m_scale = m_zoom / 100.0;
}
