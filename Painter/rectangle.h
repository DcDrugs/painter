#pragma once
#include "shapecenter.h"

class Rect : public ShapeCenter<Rect> {
private:
	Rect() : ShapeCenter<Rect>() { }



public:

	Rect(const BaseConfiguration& config) : ShapeCenter<Rect>(config) { }

	void Draw(QPainter& painter) const override;

	static std::shared_ptr<BaseShape> Instance();

};
