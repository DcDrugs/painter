#include <qfiledialog.h>
#include <memory>
#include <fstream>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRgb>
#include "draw_action_event.h"
#include "draw_hand_event.h"
#include "draw_line_event.h"
#include "painter.h"
#include "oval.h"
#include "rectangle.h"
#include "triangle.h"
#include "line.h"

Painter::Painter(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void Painter::on_create_btn_triggered() {
    _shapeManager.Clear();
    clear();
}

void Painter::clear()
{
    ClearCanvas(_canvas, width(), height());
    update();
}


void Painter::on_open_btn_triggered() {

    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"),
        "",
        tr("Painter Image (*.pmap)"));

    if (!fileName.isEmpty()) {
        _shapeManager.Clear();

        std::string current_locale_text = fileName.toLocal8Bit().constData();
        std::ifstream a(current_locale_text, std::ios::binary);

        _shapeManager.LoadAll(a);
        ReloadCanvas();
    }
}

void Painter::ReloadCanvas()
{
    ClearCanvas(_canvas, width(), height());

    QPainter painter(&_canvas);
    _shapeManager.DrawAll(painter);
    painter.end();
}

void Painter::on_save_btn_triggered() {
    auto fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"),
        "",
        tr("Painter Image (*.pmap);;All Files (*)"));

    if (!fileName.isEmpty()) {
        std::string current_locale_text = fileName.toLocal8Bit().constData();
        std::ofstream a(current_locale_text, std::ios::binary);

        _shapeManager.SaveAll(a);
    }
}

void Painter::on_create_oval_triggered() {
    _currentAction 
        = std::unique_ptr<ActionEvent>((ActionEvent*)new DrawActionEvent(_canvas, _shapeManager, width(), height(), Oval::GetStaticHashClass()));
    _currentID = Oval::GetStaticHashClass();
}

void Painter::on_create_rectangle_triggered() {
    _currentAction
        = std::unique_ptr<ActionEvent>((ActionEvent*)new DrawActionEvent(_canvas, _shapeManager, width(), height(), Rect::GetStaticHashClass()));
    _currentID = Rect::GetStaticHashClass();
}

void Painter::on_create_triangle_triggered() {
    _currentAction
        = std::unique_ptr<ActionEvent>((ActionEvent*)new DrawActionEvent(_canvas, _shapeManager, width(), height(), Triangle::GetStaticHashClass()));
    _currentID = Triangle::GetStaticHashClass();
}

void Painter::on_create_line_triggered() {
    _currentAction
        = std::unique_ptr<ActionEvent>((ActionEvent*)new DrawLineEvent(_canvas, _shapeManager, width(), height(), Line::GetStaticHashClass()));
    _currentID = Line::GetStaticHashClass();
}

void Painter::on_move_btn_triggered() {
    _currentAction
        = std::unique_ptr<ActionEvent>((ActionEvent*)new DrawHandEvent(_canvas, _shapeManager, width(), height()));
}

void Painter::mousePressEvent(QMouseEvent* event) {
    _currentAction->mousePressEvent(event);
    repaint();
}

void Painter::mouseMoveEvent(QMouseEvent* event) {
    _currentAction->mouseMoveEvent(event);
    repaint();
}

void Painter::mouseReleaseEvent(QMouseEvent* event) {
    _currentAction->mouseReleaseEvent(event);
    repaint();
}

void Painter::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    QImage newCanvas;
    ClearCanvas(newCanvas, width(), height());

    QPainter p(&newCanvas);
    p.drawImage(0, 0, _canvas);

    _canvas = newCanvas;
    ActionUpdate();
    update();
}

void Painter::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, QPixmap::fromImage(_canvas));
}

void Painter::ActionUpdate() {
    if (_currentID == -1)
        _currentID = Oval::GetStaticHashClass();
    _currentAction
        = std::unique_ptr<ActionEvent>((ActionEvent*)new DrawActionEvent(_canvas, _shapeManager, width(), height(), _currentID));
}


