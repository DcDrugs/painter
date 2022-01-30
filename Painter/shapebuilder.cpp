#include <memory>
#include "shapebuilder.h"

template<class TBased>
static std::unique_ptr<BaseShape> ShapeBuilder::Build(const BaseConfiguration& config) {
	return unique_ptr(new TBased(config));
}