#include "RotatableButton.h"
#include <QPainter>
#include <QPaintEvent>
#include <QtMath>
#include <QStylePainter>
#include <QStyleOptionButton>

RotatableButton::RotatableButton(QWidget *parent)
    : QPushButton(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

RotatableButton::RotatableButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void RotatableButton::setRotation(qreal rotation)
{
    m_rotation = rotation;
    update();
}

void RotatableButton::setButtonSize(const QSize &size)
{
    m_buttonSize = size;
    updateContainerSize();
}

void RotatableButton::updateContainerSize()
{
    // Calculate the diagonal to ensure the button fits at any rotation
    int diagonal = qCeil(qSqrt(m_buttonSize.width() * m_buttonSize.width() + 
                              m_buttonSize.height() * m_buttonSize.height()));
    
    // Set the widget size to this diagonal size
    QPushButton::setFixedSize(diagonal, diagonal);
}

void RotatableButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
}

void RotatableButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.save();

    QPointF center = rect().center();

    // Setup rotation around center
    painter.translate(center);
    painter.rotate(m_rotation);
    painter.translate(-center);

    // Calculate position to center the button in the container
    int x = (width() - m_buttonSize.width()) / 2;
    int y = (height() - m_buttonSize.height()) / 2;

    // Create and configure style option
    QStyleOptionButton option;
    initStyleOption(&option);
    option.rect = QRect(x, y, m_buttonSize.width(), m_buttonSize.height());

    style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

    painter.restore();
}
