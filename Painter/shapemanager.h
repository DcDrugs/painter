#pragma once
#include <memory>
#include <QtGui>
#include "baseshape.h"


class ShapeManager {
private:

	QList<std::shared_ptr<BaseShape>> _objs;

public:

	void DrawAll(QPainter& painter);
	void AddShape(std::shared_ptr<BaseShape> obj, std::size_t position);

	std::shared_ptr<BaseShape> Take(std::shared_ptr<BaseShape> shape);

	void Remove(size_t id);
	void Remove(QList<std::shared_ptr<BaseShape>>& lines);

	std::shared_ptr<BaseShape> TryGetClosestShape(const QPoint& pos);

	std::shared_ptr<BaseShape> FindAt(std::size_t id);
	std::size_t FindAt(std::shared_ptr<BaseShape> obj);

	std::shared_ptr<BaseShape> GetClosestShape(const QPoint& pos);

	void LoadAll(std::ifstream& loader);

	void SaveAll(std::ofstream& saver);

	void Clear();

};

class ShapeManagerBuilder {
private:
	inline static ShapeManager instance{ };
public:
	static ShapeManager& GetInstance() {
		return instance;
	}
};