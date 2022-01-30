#pragma once
#include "shapecenter.h"

class Oval : public ShapeCenter<Oval> {
private:

	Oval() : ShapeCenter<Oval>() { }

public:

	Oval(const BaseConfiguration& config) : ShapeCenter<Oval>(config) { }

	void Draw(QPainter& painter) const override;

	static std::shared_ptr<BaseShape> Instance();

};