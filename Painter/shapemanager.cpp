#include <algorithm>
#include "version.h"
#include "qtalgorithm.h"
#include "shapemanager.h"

void ShapeManager::DrawAll(QPainter& painter) {
	for (auto& obj : _objs)
	{
		obj->Draw(painter);
	}
}

void ShapeManager::AddShape(std::shared_ptr<BaseShape> obj, std::size_t position = -1) {
	if (position == -1)
		_objs.append(obj);
	else
		_objs.insert(position, obj);
}

void ShapeManager::LoadAll(std::ifstream& loader) {

	size_t version;

	loader.read((char*)&version, sizeof(version));

	if (version >= RELEASE_1_0_0) {
		int size;

		loader.read((char*)&size, sizeof(size));

		for (int i = 0; i < size; i++)
			_objs.append(BaseShape::LoadStatic(loader, version));
	}
	else
		throw std::exception("Unknown version");
}

void ShapeManager::SaveAll(std::ofstream& saver) {
	size_t version = REAL_VERSION;
	saver.write((char*)&version, sizeof(version));

	int size = _objs.size();
	saver.write((char*)&size, sizeof(size));

	for (auto& obj : _objs)
		BaseShape::SaveStatic(saver, obj);
}

void ShapeManager::Clear() {
	_objs.clear();
}

std::shared_ptr<BaseShape> ShapeManager::TryGetClosestShape(const QPoint& pos) {
	if(_objs.size() == 0)
		return std::shared_ptr<BaseShape>();

	auto obj = *std::min_element(_objs.begin(), _objs.end(), [&pos](const auto& that, const auto& smallest) {
		return (Distance(that->TryGetCenter(), pos) == Distance(smallest->TryGetCenter(), pos))? false :
			Distance(that->TryGetCenter(), pos) < Distance(smallest->TryGetCenter(), pos);
		});

	if (obj->TryGetCenter() == BaseShape::InfinityPoint)
		return std::shared_ptr<BaseShape>();
	return obj;
}

std::shared_ptr<BaseShape> ShapeManager::GetClosestShape(const QPoint& pos) {

	auto obj = TryGetClosestShape(pos);
	if (obj.get() == nullptr)
		throw std::exception("Shape not found");
	return obj;
}

std::shared_ptr<BaseShape> ShapeManager::Take(std::shared_ptr<BaseShape> shape) {
	_objs.removeOne(shape);
	return shape;
}

std::shared_ptr<BaseShape> ShapeManager::FindAt(std::size_t id) {
	return _objs.at(id);
}

std::size_t ShapeManager::FindAt(std::shared_ptr<BaseShape> obj) {
	return _objs.indexOf(obj);
}