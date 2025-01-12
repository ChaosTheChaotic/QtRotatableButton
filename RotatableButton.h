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
    void setButtonSize(const QSize &size);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateContainerSize();
    qreal m_rotation = 0;
    QSize m_buttonSize;  // Actual visual button size
};

#endif // ROTATABLEBUTTON_H
