#pragma once
#include <bitset>
#include <vector>

#include "Pool.h"

constexpr unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> signature;

struct IComponent
{
protected:
	static int nextId;
};

template <typename T>
class Component : public IComponent
{
private:
	int _id;
public:
	explicit Component(const int id) : _id(id) {}

	static int GetId()
	{
		static auto id = nextId++;
		return id;
	}
};

class Entity
{
private:
	int _id;
public:
	explicit Entity(const int id) : _id(id) {}
	Entity(const Entity& entity) = default;

	[[nodiscard]] int GetId() const { return _id; }

	// todo test that this swaps in memory, otherwise:
	// binary search the entity vector
	// reassign the address of the entity to point to the new entity
	Entity&  operator=(const Entity& other) = default;
	bool operator==(const Entity& other) const
	{
				return _id == other._id;
	}

	bool operator!=(const Entity& other) const
	{
				return _id != other._id;
	}

	bool operator<(const Entity& other) const
	{
						return _id < other._id;
	}

	bool operator>(const Entity& other) const
	{
		return _id > other._id;
	}
};

/**
 * \ brief Base class for all systems that process entities
 */
class System
{
private:
	/**
	 * \brief bitset to store the signature of the system
	 */
	signature _componentSignature;

	/**
	 * \brief entities belonging to the system
	 */
	std::vector<Entity> _entities;

public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
	[[nodiscard]] std::vector<Entity> GetSystemEntities() const;
	[[nodiscard]] const signature& GetComponentSignature() const;

	/**
	 * \brief Defines the component type that the system requires
	 * \tparam TComponent Component type implementing IComponent
	 */
	template <typename TComponent> void RequireComponent();

};

class Registry
{
private:
	int numEntities = 0;
	std::vector<IPool*> _componentPools;
	std::vector<signature> _entityComponentSignatures;;

public:
	Entity CreateEntity();
	void KillEntity();
	void AddSystem();
	void AddComponent();
	// ...
};

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	_componentSignature.set(componentId);
}
