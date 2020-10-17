#pragma once

#include <engine/ecs/ECS.h>
#include <engine/ecs/Components.h>

#include <engine/ui/UIElement.h>

#include <engine/utils/Vector2.h>

namespace engine {

class UI {
public:
	template <typename T, typename ...TArgs>
	static ecs::Entity AddButton(ecs::Manager& ui_manager, ecs::Manager& manager, V2_int position, V2_int size, UIElement button_info) {
		auto button = ui_manager.CreateEntity();
		EventHandler::Register<T, TArgs...>(button);
		button.AddComponent<UIComponent>(button_info, &manager);
		button.AddComponent<TransformComponent>(position);
		button.AddComponent<SizeComponent>(size);
		button.AddComponent<RenderComponent>();
		return button;
	}
private:

};

} // namespace engine