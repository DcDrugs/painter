#pragma once
#include "baseshape.h"
#include "configuration.h"

class ShapeBuilder {

public:

	template<class TBased>
	static std::unique_ptr<BaseShape> Build(const BaseConfiguration& config);
};