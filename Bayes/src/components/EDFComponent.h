#pragma once

struct EDFComponent {
	EDFComponent(double max_thrust_force) : max_thrust_force{ max_thrust_force } {}
	double thrust_force = 0.0;
	double max_thrust_force;
	double thrust_ramp_up_speed = 0.4;
	double thrust_ramp_up = 0.0;
	double thrust_percent = 1.0;
	double com_tvc = 0.3; // Distance between center of mass and tvc (m).
	void Power() {
		thrust_ramp_up = engine::math::Clamp(thrust_ramp_up, 0.0, 1.0);
		thrust_percent = engine::math::Clamp(thrust_percent, 0.0, 1.0);
		thrust_force = max_thrust_force * thrust_ramp_up * thrust_percent;
	}
	void Activate(double thrust) {
		thrust_force = engine::math::Clamp(thrust, 0.0, max_thrust_force);
	}
	void Deactivate() {
		thrust_force = 0.0;
		thrust_ramp_up = 0.0;
		thrust_percent = 1.0;
	}
	double GetTorque(double angle) {
		engine::math::Clamp(angle, -20.0, 20.0); // this stops the controller from being able to use huge control values
		return std::sin(engine::math::DegreeToRadian(angle)) * thrust_force * com_tvc;
	}
};