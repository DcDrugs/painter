#include "draw_hand_event.h"


void DrawHandEvent::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {

        _obj = _shapeManager.TryGetClosestShape(event->pos());
        _position = _shapeManager.FindAt(_obj);

        if (_obj.get() == nullptr)
            return;

        if (!PointInRectangle(_obj->GetStart(), _obj->GetEnd(), event->pos()))
            return;

        _obj = _shapeManager.Take(_obj);

        ClearCanvas(_canvas, width, height);

        QPainter painter(&_canvas);

        _shapeManager.DrawAll(painter);

        painter.end();
    }

}

void DrawHandEvent::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        ClearCanvas(_canvas, width, height);

        if (_obj.get() == nullptr)
            return;

        QPainter painter(&_canvas);

        _shapeManager.DrawAll(painter);

        painter.end();

        _obj->MoveOnPosition(event->pos());

        Draw(_obj, _canvas);
    }
}

void  DrawHandEvent::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() & Qt::LeftButton) {
        ClearCanvas(_canvas, width, height);

        if (_obj.get() == nullptr)
            return;

        _obj->MoveOnPosition(event->pos());

        _shapeManager.AddShape(_obj, _position);

        QPainter painter(&_canvas);

        _shapeManager.DrawAll(painter);

        painter.end();
    }

}