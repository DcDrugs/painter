#include "draw_action_event.h"

void DrawActionEvent::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        _lastCanvas = _canvas;
        _lastPoint = event->pos();
    }
}

void DrawActionEvent::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        ClearCanvas(_canvas, width, height);
        _canvas = _lastCanvas;

        TryDraw(_lastPoint, event->pos(), _currentID, _canvas);
    }
}

void DrawActionEvent::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() & Qt::LeftButton) {
        ClearCanvas(_canvas, width, height);
        _canvas = _lastCanvas;
        _shapeManager.AddShape(TryDraw(_lastPoint, event->pos(), _currentID, _canvas), -1);
        _lastPoint = QPoint();
    }

}