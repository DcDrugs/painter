#include "line.h"
#include "shapemanager.h"
#include "version.h"

void Line::SetShape(std::shared_ptr<BaseShape> from, std::shared_ptr<BaseShape> to) {
	_from = from;
	_idFrom = ShapeManagerBuilder::GetInstance().FindAt(from);
	_from->AddLine((BaseShape*)this);
	_to = to;
	_idTo = ShapeManagerBuilder::GetInstance().FindAt(to);
	_to->AddLine((BaseShape*)this);
	_start = _from->GetCenter();
	_end = _to->GetCenter();
}

void Line::Save(std::ofstream& saver) const {

	auto from = _idFrom;
	auto to = _idTo;

	saver.write((char*)&from, sizeof(from));
	saver.write((char*)&to, sizeof(to));
}

void Line::Draw(QPainter& painter) const {
	painter.drawLine(_start, _end);
}

void Line::Load(std::ifstream& loader, size_t version) {

	if (version >= REAL_VERSION) {
		size_t a, b;

		loader.read((char*)&a, sizeof(a));
		loader.read((char*)&b, sizeof(b));

		_idFrom = a;
		_from = ShapeManagerBuilder::GetInstance().FindAt(a);
		_from->AddLine((BaseShape*)this);
		_idTo = b;
		_to = ShapeManagerBuilder::GetInstance().FindAt(b);
		_to->AddLine((BaseShape*)this);
		_start = _from->GetCenter();
		_end = _to->GetCenter();
	}
}


std::shared_ptr<BaseShape> Line::Instance() {
	return std::shared_ptr<BaseShape>(new Line());
}

void Line::TryRecalculateCenter() {

}

void Line::RecalculateCenter() {
	throw std::exception("Line has no center");
}

QPoint Line::TryGetCenter() const {
	return BaseShape::InfinityPoint;
}

QPoint Line::GetCenter() const {
	throw std::exception("Line has no center");
}

void Line::MoveOnPosition(QPoint center) {
	throw std::exception("Line can not move");
}

void Line::ChangeCenter(QPoint last, QPoint center) {
	if (_start == last)
		_start = center;
	else
		_end = center;
}

void Line::AddLine(BaseShape* line) {
	throw std::exception("can not add line to line");
}