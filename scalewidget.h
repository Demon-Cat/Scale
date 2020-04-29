#ifndef SCALEWIDGET_H
#define SCALEWIDGET_H

#include <QWidget>

class ScaleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScaleWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

signals:

public slots:

private:
    QPoint m_pressDistance;

    //100-1000
    int m_zoom = 100;
    qreal m_scale = 1;
};

#endif // SCALEWIDGET_H
