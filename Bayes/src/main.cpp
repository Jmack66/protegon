#include <engine/Include.h>

#include "components/Components.h"
#include "factory/Factories.h"
#include "systems/Systems.h"

#include <cmath>

class Hopper : public engine::Engine {
public:
	void Init() {

		/*V2_int graph_size = { 400, 400 };
		auto [graph_window, graph_renderer] = GenerateWindow("Graph", { 50, 50 }, graph_size);
		scene.manager.AddSystem<GraphSystem>(graph_renderer, graph_size);*/
		LOG("Initializing hopper systems...");
		scene.manager.AddSystem<HopperRenderSystem>(&scene);
		scene.manager.AddSystem<WorldRenderSystem>(&scene);
		scene.manager.AddSystem<HopperPhysicsSystem>();
		scene.manager.AddSystem<HopperCollisionSystem>();

		CreateWorld(scene.manager);

		LOG("Initialized all game systems successfully");
	}
	void Reset() {
		scene.manager.Clear();
		CreateWorld(scene.manager);
		LOG("RESETTING SIMULATION");
		LOG("RESETTING SIMULATION");
		LOG("RESETTING SIMULATION");
		LOG("RESETTING SIMULATION");
		LOG("RESETTING SIMULATION");
	}



    void Update() {
		static int counter = 0;
		if (engine::InputHandler::KeyDown(Key::R)) {
			Reset();
		} else {
			if (scene.manager.HasSystem<HopperPhysicsSystem>()) {

				auto players = scene.manager.GetComponentTuple<PlayerController, TransformComponent, RigidBodyComponent, StateVectorComponent, EDFComponent, HopperComponent>();
				for (auto [entity, player, transform, rigid, state_vector, edf, hopper] : players) {
					auto& rb = rigid.rigid_body;
					auto& state = state_vector;
					if (engine::InputHandler::KeyDown(Key::UP)) {
						edf.thrust_percent += 0.2;
					} else if (engine::InputHandler::KeyDown(Key::DOWN)) {
						edf.thrust_percent -= 0.2;
					}
					if (engine::InputHandler::KeyPressed(Key::SPACE)) {
						edf.thrust_ramp_up += edf.thrust_ramp_up_speed;
						edf.Power();
					}

					double disturbance_torque = 0;
					//auto proportional_gain = 0.9;
					if (engine::InputHandler::KeyPressed(Key::RIGHT)) {
						disturbance_torque = 3;
					} else if (engine::InputHandler::KeyPressed(Key::LEFT)) {
						disturbance_torque = -3;
					}
					state.Update((double)transform.position.x - 416.0, (double)rb.velocity.x, (double)transform.position.y - 320.0, (double)rb.velocity.y, (double)transform.rotation, (double)hopper.theta_d);
					Vector2<double> control = state.ComputeControl();
					LOG(state.theta_dot);
					edf.Activate(-control.x);
					double control_torque = edf.GetTorque(control.y);
					//double control_torque = 0.0;
					hopper.theta_dd = (disturbance_torque + control_torque) / hopper.inertia * 0.005;
					rb.acceleration.y -= edf.thrust_force * abs(std::cos(engine::math::DegreeToRadian(transform.rotation))) / rb.mass;
					rb.acceleration.x += edf.thrust_force * std::sin(engine::math::DegreeToRadian(transform.rotation)) / rb.mass;
					if (std::abs(transform.rotation) > 180) {
						Reset();
					}
				}

				scene.manager.Update<HopperPhysicsSystem>();
			}
			scene.manager.Update<HopperCollisionSystem>();
		}
    }

	void Render() {
		//scene.manager.Update<GraphSystem>();
		scene.manager.Update<HopperRenderSystem>();
		scene.manager.Update<WorldRenderSystem>();
	}
private:
};

int main(int argc, char* args[]) { // sdl main override

	LOG("Starting Hopper Simulation");
	engine::Engine::Start<Hopper>("Hopper Simulation", 1000, 600);

    return 0;
}