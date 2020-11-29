#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    Ui::Widget *ui;

private slots:
    void handleButton();
    void hzLarger();
    void hzSmaller();
    void hzItalic();
    void hzRotate();
    void hzColor();
private:
    QPushButton* myButton;
    QPushButton* btn_larger;
    QPushButton* btn_smaller;
    QPushButton* btn_italic;
    QPushButton* btn_rotate;
    QPushButton* btn_color;
    QLineEdit* input;
};
#endif // WIDGET_H
