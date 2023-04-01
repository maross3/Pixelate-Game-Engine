#include "ECS.h"
void System::AddEntityToSystem(Entity entity)
{
	_entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{
	// binary search for the entity
	auto left = 0;
	auto right = _entities.size() - 1;
	const auto target = entity.GetId();
	
	while (left < right)
	{
		const auto pivot = left + (right - left) / 2;
		if (_entities[pivot].GetId() == target)
		{
			_entities.erase(_entities.begin() + pivot);
			break;
		}
		if (_entities[pivot].GetId() < target)
			left = pivot + 1;
		else
			right = pivot - 1;
	}
}

std::vector<Entity> System::GetSystemEntities() const
{ return _entities; }

const signature& System::GetComponentSignature() const
{
	return _componentSignature;
}


