#pragma once
#include "shape.h"
#include "qtalgorithm.h"
#include "line.h"

template<class TBased>
class ShapeCenter : public Shape<TBased> {
protected:

	ShapeCenter() : Shape<TBased>() { }

	QPoint _center;
	QSize _size;

	QList<BaseShape*> lines;

public:

	QPoint TryGetCenter() const override {
		return _center;
	}

	void RecalculateCenter() override {
		_center = QPoint((BaseShape::_start.x() + BaseShape::_end.x()) / 2, (BaseShape::_start.y() + BaseShape::_end.y()) / 2);
	}

	ShapeCenter(const BaseConfiguration& config) : Shape<TBased>(config) {
		_size = GetSize(BaseShape::_start, BaseShape::_end);
		RecalculateCenter();
	}

	void Draw(QPainter& painter) const override = 0;

	void MoveOnPosition(QPoint center) override {
		auto dx = _center.x() - center.x();
		auto dy = _center.y() - center.y();
		BaseShape::_start -= QPoint(dx, dy);
		BaseShape::_end -= QPoint(dx, dy);
		auto last = _center;

		_center = center;

		for (auto& line: lines) {
			dynamic_cast<Line*>(line)->ChangeCenter(last, _center);
		}
		
	}

	void TryRecalculateCenter() override {
		RecalculateCenter();
	}

	void Load(std::ifstream& loader, size_t version) override {
		BaseShape::Load(loader, version);
		_size = GetSize(BaseShape::_start, BaseShape::_end);
		RecalculateCenter();
	}

	void Init(const BaseConfiguration& config) override {
		BaseShape::Init(config);
		_size = GetSize(BaseShape::_start, BaseShape::_end);
		RecalculateCenter();
	}

	void AddLine(BaseShape* line) {
		lines.append(line);
	}

};