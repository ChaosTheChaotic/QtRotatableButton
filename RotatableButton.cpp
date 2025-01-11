#include "RotatableButton.h"
#include <QPainter>
#include <QPaintEvent>
#include <QtMath>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QDebug>

RotatableButton::RotatableButton(QWidget *parent)
    : QPushButton(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_baseSize = QPushButton::sizeHint();
    updateButtonGeometry();
}

RotatableButton::RotatableButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_baseSize = QPushButton::sizeHint();
    updateButtonGeometry();
}

void RotatableButton::setRotation(qreal rotation)
{
    m_rotation = rotation;
    update();
}

void RotatableButton::updateButtonGeometry()
{
    // Calculate diagonal length as the maximum possible size needed
    int diagonal = qCeil(qSqrt(m_baseSize.width() * m_baseSize.width() + 
                              m_baseSize.height() * m_baseSize.height()));
    
    // Set size to a square that can contain the button at any rotation
    setFixedSize(diagonal, diagonal);
}

void RotatableButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.save();

    QPointF center = rect().center();

    // Move to center, rotate, then move back
    painter.translate(center);
    painter.rotate(m_rotation);
    painter.translate(-center);

    // Calculate the position to center the base button in the widget
    int x = (width() - m_baseSize.width()) / 2;
    int y = (height() - m_baseSize.height()) / 2;

    QStyleOptionButton option;
    initStyleOption(&option);
    option.rect = QRect(x, y, m_baseSize.width(), m_baseSize.height());

    style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

    painter.restore();
}

QSize RotatableButton::sizeHint() const
{
    return size();
}

QSize RotatableButton::minimumSizeHint() const
{
    return size();
}
