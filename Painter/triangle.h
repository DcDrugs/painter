#pragma once
#include "shapecenter.h"

class Triangle : public ShapeCenter<Triangle> {
private:

	Triangle() : ShapeCenter<Triangle>() { }

public:

	Triangle(const BaseConfiguration& config) : ShapeCenter<Triangle>(config) { }

	void Draw(QPainter& painter) const override;

	static std::shared_ptr<BaseShape> Instance();
};