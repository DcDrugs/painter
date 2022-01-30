#include <exception>
#include "baseshape.h"
#include "qtalgorithm.h"
#include "version.h"

BaseShape::BaseShape(){ }


BaseShape::BaseShape(const BaseConfiguration& config) {
	_start = config.start;
	_end = config.end;
	TryRecalculateCenter();
}


std::shared_ptr<BaseShape> BaseShape::LoadStatic(std::ifstream& loader, int version) {
	if (version >= RELEASE_1_0_0) {
		Hash<BaseShape>::HashType hash;
		loader.read((char*)&hash, sizeof(hash));

		auto shape = Hash<BaseShape>::GetInstance(hash)();

		shape->Load(loader, version);

		return std::move(shape);
	}
	else
		throw std::exception("Unknown version");
}

void BaseShape::Load(std::ifstream& loader, size_t version) {
	auto start = LoadQPoint(loader);
	auto end = LoadQPoint(loader);


	_start = start;
	_end = end;
}

void BaseShape::SaveStatic(std::ofstream& saver, const std::shared_ptr<BaseShape>& obj) {
		auto hash = obj->GetHashClass();
		saver.write((char*)&hash, sizeof(hash));

		obj->Save(saver);
}

void BaseShape::Save(std::ofstream& saver) const {
	SaveQPoint(saver, _start);
	SaveQPoint(saver, _end);
}

QPoint BaseShape::GetStart() const {
	return _start;
}

QPoint BaseShape::GetEnd() const {
	return _end;
}

const std::shared_ptr<BaseShape> BaseShape::GetInstanceObject(Hash<BaseShape>::HashType key, const BaseConfiguration& config) {
	auto obj = Hash<BaseShape>::GetInstance(key)();
	obj->Init(config);
	return obj;
}

void BaseShape::Init(const BaseConfiguration& config) {
	_start = config.start;
	_end = config.end;
	TryRecalculateCenter();
}

QPoint BaseShape::TryGetCenter() const {
	return InfinityPoint;
}

QPoint BaseShape::GetCenter() const {
	auto p = TryGetCenter();
	if (p == InfinityPoint)
		throw std::exception("this shape has not center");
	return p;
}

void BaseShape::RecalculateCenter() {
	throw std::exception("this shape has not center");
}

void BaseShape::TryRecalculateCenter() { }

