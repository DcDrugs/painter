#include "oval.h"

void Oval::Draw(QPainter& painter) const {
	painter.drawEllipse(_start.x(), _start.y(), _size.width(), _size.height());
}

std::shared_ptr<BaseShape> Oval::Instance() {
	return std::shared_ptr<BaseShape>(new Oval());
}