#ifndef ROTATABLEBUTTON_H
#define ROTATABLEBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class RotatableButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    explicit RotatableButton(QWidget *parent = nullptr);
    explicit RotatableButton(const QString &text, QWidget *parent = nullptr);
    qreal rotation() const { return m_rotation; }
    void setRotation(qreal rotation);
    QSize baseSize() const { return m_baseSize; }

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    void updateButtonGeometry();
    qreal m_rotation = 0;
    QSize m_baseSize;
};

#endif // ROTATABLEBUTTON_H
