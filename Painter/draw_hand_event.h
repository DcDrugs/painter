#pragma once
#include "action_event.h"

class DrawHandEvent : ActionEvent {
private:

    QImage& _canvas;

    std::shared_ptr<BaseShape> _obj;

    ShapeManager& _shapeManager;

    std::size_t _position;

    int width;
    int height;


public:

    DrawHandEvent(QImage& canvas,
        ShapeManager& shapeManager,
        int width,
        int height) : _canvas(canvas), _shapeManager(shapeManager),
        width(width), height(height) { }

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void  mouseReleaseEvent(QMouseEvent* event) override;

};