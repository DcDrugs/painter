#pragma once
#include <fstream>
#include <memory>
#include <QtGui>
#include <unordered_set>

#include "configuration.h"
#include "hash.h"

class BaseShape : public Hash<BaseShape> {
public:

	BaseShape();

	BaseShape(const BaseConfiguration& config);

	virtual QPoint TryGetCenter() const;

	virtual QPoint GetCenter() const;

	virtual void TryRecalculateCenter();

	virtual void RecalculateCenter();

	virtual void MoveOnPosition(QPoint center) = 0;

	static const std::shared_ptr<BaseShape> GetInstanceObject(Hash<BaseShape>::HashType key, const BaseConfiguration& config);

	virtual void Init(const BaseConfiguration& config);

	virtual QPoint GetStart() const;

	virtual QPoint GetEnd() const;

	static std::shared_ptr<BaseShape> LoadStatic(std::ifstream& loader, int version);

	virtual void Save(std::ofstream& saver) const;

	static void SaveStatic(std::ofstream& saver, const std::shared_ptr<BaseShape>& obj);

	virtual void Load(std::ifstream& loader, size_t version);

	virtual void Draw(QPainter& painter) const = 0;

	virtual void AddLine(BaseShape* line) = 0;

	inline static QPoint InfinityPoint{ -10000, -10000 };

protected:

	QPoint _start;
	QPoint _end;

};
