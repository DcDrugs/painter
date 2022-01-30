#pragma once
#include <unordered_set>
#include <string>
#include <qstring.h>
#include <stdexcept>
#include "baseshape.h"
#include "method_checker.h"

#include <locale>
#include <codecvt>

template<class TBased>
class Shape : public BaseShape{

private:
	using Hash::values;

	inline static size_t _hash = Hash::IncClassHash();

	class Hasher {
	public:
		Hasher(Hash::InstanceMap& values, Hash::HashType hash) {
			static_assert(HasLoad<TBased>::value, "\"static std::unique_ptr<BaseShape> Instance()\" not found (C2039): ");
			values[_hash] = TBased::Instance;
		}
	};

	inline static Hasher hasher = Hasher(values, _hash);

protected:

	Shape() : BaseShape() { }

public:

	Shape(const BaseConfiguration& config) : BaseShape(config) { }

	static Hash<BaseShape>::HashType GetStaticHashClass() {
		return _hash;
	}

	Hash<BaseShape>::HashType GetHashClass() override {
		return GetStaticHashClass();
	}

	void Draw(QPainter& painter) const override = 0;

};