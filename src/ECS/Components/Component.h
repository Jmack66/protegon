#pragma once

#include "BaseComponent.h"

#include "../Entity.h"

template <class T>
class Component : public BaseComponent {
public:
	// TODO: This constructor should be taking in the [parent entity] / [parent manager + entityID] reference
	// Each Component implementation will have a constructor that takes in the above mentioned information and passes it to the Component() constructor
	// Consider how this is effected by the construction of components in addComponents, they will each require a manager reference and an entity
	virtual BaseComponent* clone() const override final {
		return new T(static_cast<const T&>(*this));
	}
	virtual std::unique_ptr<BaseComponent> uniqueClone() const override final {
		return std::make_unique<T>(static_cast<const T&>(*this));
	}
	virtual void serialize(nlohmann::json& j) override final {
		j[getName()] = static_cast<T&>(*this);
	}
	virtual void setup() override {}
	virtual void setHandle(Entity handle) override final {
		entity = handle;
	}
	virtual ComponentName getName() override final {
		return typeid(T).name();
	}
protected:
	Entity entity;
};