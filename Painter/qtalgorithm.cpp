#include <math.h>
#include "qtalgorithm.h"


int Distance(const QPoint& lhs, const QPoint& rhs) {
	return std::sqrt(std::pow((lhs.x() - rhs.x()), 2) + std::pow((lhs.y() - rhs.y()), 2));
}


QPoint LoadQPoint(std::ifstream& loader) {
	int x;
	int y;
	loader.read((char*)&x, sizeof(x));
	loader.read((char*)&y, sizeof(y));
	return QPoint(x, y);
}

void SaveQPoint(std::ofstream& saver,const QPoint& obj) {
	auto x = obj.x();
	auto y = obj.y();
	saver.write((char*)&x, sizeof(x));
	saver.write((char*)&y, sizeof(y));
}


QSize GetSize(const QPoint& _start, const QPoint& _end) {
	return QSize(_end.x() - _start.x(), _end.y() - _start.y());
}

void ClearCanvas(QImage& canvas, int width, int height)
{
	canvas = QImage(width, height, QImage::Format_RGB888);
	canvas.fill(QColor(Qt::white));
}

bool PointInRectangle(const QPoint& start, const QPoint& end, const QPoint& point) {
	return (point.x() > start.x() && point.x() < end.x() && point.y() > start.y() && point.y() < end.y());
}