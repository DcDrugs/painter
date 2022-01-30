#pragma once
#include "shape.h"

class Line : public Shape<Line> {
private:

	Line() : Shape<Line>() { }

	std::shared_ptr<BaseShape> _from;
	std::size_t _idFrom;
	std::shared_ptr<BaseShape> _to;
	std::size_t  _idTo;

public:

	void SetShape(std::shared_ptr<BaseShape> from, std::shared_ptr<BaseShape> to);

	void Save(std::ofstream& saver) const override;

	void Draw(QPainter& painter) const override;

	void Load(std::ifstream& loader, size_t version);

	static std::shared_ptr<BaseShape> Instance();

	void TryRecalculateCenter() override;

	void RecalculateCenter() override;

	QPoint TryGetCenter() const override;

	QPoint GetCenter() const override;

	void MoveOnPosition(QPoint center) override;

	void ChangeCenter(QPoint last, QPoint center);

	void AddLine(BaseShape* line) override;
};