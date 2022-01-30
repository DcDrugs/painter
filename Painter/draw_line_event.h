#pragma once
#include "action_event.h"

class DrawLineEvent : ActionEvent {
private:

    QImage& _canvas;
    QImage _lastCanvas;

    std::shared_ptr<BaseShape> _lastShape;

    BaseShape::HashType _currentID;

    ShapeManager& _shapeManager;

    int width;
    int height;


public:

    DrawLineEvent(QImage& canvas,
        ShapeManager& shapeManager,
        int width,
        int height,
        BaseShape::HashType id) : _canvas(canvas), _shapeManager(shapeManager),
        width(width), height(height), _currentID(id) { }

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void  mouseReleaseEvent(QMouseEvent* event) override;

};