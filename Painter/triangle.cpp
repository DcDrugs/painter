#include "triangle.h"


void Triangle::Draw(QPainter& painter) const {

	QList<QPoint> points;

	points.append(_end);
	points.append(QPoint(_start.x() + (_end.x() - _start.x()) / 2, _start.y()));
	points.append(QPoint(_start.x() + (_end.x() - _start.x()) / 2, _start.y()));
	points.append(QPoint(_start.x(), _end.y()));
	points.append(QPoint(_start.x(), _end.y()));
	points.append(_end);

	painter.drawLines(points);
}

std::shared_ptr<BaseShape> Triangle::Instance() {
	return std::shared_ptr<BaseShape>(new Triangle());
}