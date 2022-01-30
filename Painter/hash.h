#pragma once
#include <qmap.h>
#include <memory>
#include <fstream>
#include <functional>


template<class TBased>
class Hash {
public:
	using HashType = std::size_t;
	using Instance = std::function<std::shared_ptr<TBased>()>;
	using InstanceMap = QMap<HashType, Instance>;

	virtual Hash<TBased>::HashType GetHashClass() = 0;

protected:

	static const Instance& GetInstance(HashType key) {
		return *values.constFind(key);
	}

	inline static InstanceMap values;

	static size_t IncClassHash() {
		static size_t i = 0;
		return i++;
	}
};
