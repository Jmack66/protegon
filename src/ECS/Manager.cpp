
#include "Manager.h"

bool Manager::init() {
	create<SystemFactory>(RenderSystem(), MovementSystem(), GravitySystem(), LifetimeSystem(), AnimationSystem(), DeadStateSystem(), CollisionSystem());
	return true;
}

Entity& Manager::getEntity(EntityID entityID) {
	auto iterator = _entities.find(entityID);
	assert(iterator != _entities.end() && "Must return valid reference to entityID");
	return *iterator->second; // reference to entity unique ptr
}

static EntityID getNewEntityID() {
	static EntityID lastID = 0U;
	return lastID++;
}

Entity& Manager::createEntity() {
	EntityID id = getNewEntityID();
	std::unique_ptr<Entity> uPtr = std::make_unique<Entity>(id, this);
	Entity& ref = *uPtr;
	_entities.emplace(id, std::move(uPtr));
	return ref;
}

void Manager::destroyEntity(EntityID entityID) {
	auto iterator = _entities.find(entityID);
	assert(iterator != _entities.end() && "Attempting to destroy non-existent entity");
	for (auto& pair : _systems) {
		pair.second->onEntityDestroyed(entityID);
	}
	_entities.erase(entityID);
}

EntityID Manager::createTree(float x, float y) {
	EntityID entityID = create<EntityFactory>(TransformComponent(Vec2D(x, y)), SizeComponent(Vec2D(32, 32)), SpriteComponent("./resources/textures/enemy.png", Vec2D(16, 16)), RenderComponent());
	return entityID;
}
EntityID Manager::createBox(float x, float y) {
	EntityID entityID = create<EntityFactory>(TransformComponent(Vec2D(x, y)), SizeComponent(Vec2D(50, 50)), SpriteComponent("./resources/textures/player_anim.png", Vec2D(16, 16), 8), AnimationComponent(0.08f), MotionComponent(Vec2D(0.1f, 0.1f)), RenderComponent(), CollisionComponent());
	Entity& entity = getEntity(entityID);
	entity.addComponents(StateComponent(entity));
	entity.getComponent<StateComponent>()->_sm.setState<AliveState>();
	return entityID;
}
EntityID Manager::createGhost(float x, float y, float lifetime) {
	EntityID entityID = create<EntityFactory>(TransformComponent(Vec2D(x, y)), SizeComponent(Vec2D(32, 32)), MotionComponent(Vec2D(0.2f, 0.0f)), CollisionComponent(), RenderComponent());
	return entityID;
}

void Manager::updateSystems() {
	getSystem<AnimationSystem>()->update();
	getSystem<GravitySystem>()->update();
	getSystem<MovementSystem>()->update();
	getSystem<CollisionSystem>()->update();
	getSystem<LifetimeSystem>()->update();
	refresh();
	getSystem<DeadStateSystem>()->update();
	refresh();
}

void Manager::refreshSystems(const EntityID entityID) {
	for (auto& pair : _systems) {
		pair.second->onEntityChanged(entityID);
	}
}

void Manager::refreshSystems() {
	for (auto& pair : _entities) {
		refreshSystems(pair.first);
	}
}

void Manager::refresh() { // REWORK
	std::vector<Entity*> deletables;
	for (auto& pair : _entities) {
		if (!pair.second->isAlive()) {
			deletables.emplace_back(pair.second.get());
		}
	}
	for (Entity* entity : deletables) {
		destroyEntity(entity->getID());
	}
	deletables.clear();
}