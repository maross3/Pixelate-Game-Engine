#pragma once
#include <vector>

class IPool
{
public:
	virtual ~IPool();
};

template <typename T>
class Pool : IPool
{
private:
	std::vector<T> _data;

public:
	explicit Pool(const int size = 100) { Resize(size); }
	virtual ~Pool() = default;

	[[nodiscard]] bool IsEmpty() const { return _data.empty(); }
	[[nodiscard]] int GetSize() const { return _data.size(); }

	void Resize(int n) { _data.resize(n); }
	void Clear() { _data.clear(); }
	void Add(T object) { return _data.push_back(object); }
	void Set(T object, int i) { _data[i] = object; }
	T& Get() { return static_cast<T&>(_data.data()); }
	T& operator[](int i) { return _data[i]; }
};
