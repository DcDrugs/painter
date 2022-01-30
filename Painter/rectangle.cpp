#include "rectangle.h"

void Rect::Draw(QPainter& painter) const {
	painter.drawRect(_start.x(), _start.y(), _size.width(), _size.height());
}

std::shared_ptr<BaseShape> Rect::Instance() {
	return std::shared_ptr<BaseShape>(new Rect());
}