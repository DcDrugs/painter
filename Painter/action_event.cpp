#include "action_event.h"

std::shared_ptr<BaseShape> ActionEvent::Draw(std::shared_ptr<BaseShape> obj, QImage& canvas) {

    QPainter painter(&canvas);

    obj->Draw(painter);

    painter.end();

    return obj;
}

std::shared_ptr<BaseShape> ActionEvent::Draw(const QPoint& start, const QPoint& end, BaseShape::HashType currentID, QImage& canvas) {
    BaseConfiguration config = { start, end };

    return Draw(BaseShape::GetInstanceObject(currentID, config), canvas);
}


std::shared_ptr<BaseShape> ActionEvent::TryDraw(const QPoint& pos1, const QPoint& pos2, BaseShape::HashType currentID, QImage& canvas) {
    auto start = QPoint(std::min(pos1.x(), pos2.x()), std::min(pos1.y(), pos2.y()));
    auto end = QPoint(std::max(pos1.x(), pos2.x()), std::max(pos1.y(), pos2.y()));
    return Draw(start, end, currentID, canvas);
}