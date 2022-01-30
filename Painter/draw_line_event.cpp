#include "draw_line_event.h"


void DrawLineEvent::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        _lastCanvas = _canvas;

        auto obj = _shapeManager.TryGetClosestShape(event->pos());

        if (obj.get() == nullptr)
            return;

        _lastShape = obj;
    }
}

void DrawLineEvent::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        ClearCanvas(_canvas, width, height);
        _canvas = _lastCanvas;

        auto obj = _shapeManager.TryGetClosestShape(event->pos());

        if (obj.get() == nullptr)
            return;

        if (_lastShape->GetCenter() == obj->GetCenter())
            return;

        Draw(_lastShape->GetCenter(), obj->GetCenter(), _currentID, _canvas);
    }
}

void  DrawLineEvent::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() & Qt::LeftButton) {
        ClearCanvas(_canvas, width, height);
        _canvas = _lastCanvas;

        auto obj = _shapeManager.TryGetClosestShape(event->pos());

        if (obj.get() == nullptr)
            return;

        if (_lastShape->GetCenter() == obj->GetCenter())
            return;

        auto line = Draw(_lastShape->GetCenter(), obj->GetCenter(), _currentID, _canvas);
        dynamic_cast<Line*>(line.get())->SetShape(_lastShape, obj);

        _shapeManager.AddShape(line, -1);
        _lastShape = std::shared_ptr<BaseShape>();
    }

}