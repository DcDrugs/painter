#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_painter.h"
#include "shapemanager.h"
#include "action_event.h"

class Painter : public QMainWindow
{
    Q_OBJECT

public:
    Painter(QWidget *parent = Q_NULLPTR);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void on_create_btn_triggered();
    void on_open_btn_triggered();
    void on_save_btn_triggered();
    void on_create_oval_triggered();
    void on_create_rectangle_triggered();
    void on_create_triangle_triggered();
    void on_create_line_triggered();
    void on_move_btn_triggered();
    void clear();

private:
    void ReloadCanvas();
    void ActionUpdate();

    QImage _canvas;

    ShapeManager& _shapeManager = ShapeManagerBuilder::GetInstance();

    std::unique_ptr<ActionEvent> _currentAction;
    BaseShape::HashType _currentID = -1;

    Ui::PainterClass ui;

};
