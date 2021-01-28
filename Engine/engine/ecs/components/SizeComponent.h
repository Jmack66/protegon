#pragma once

#include "utils/math/Vector2.h"

struct SizeComponent {
	SizeComponent(V2_double size) : size{ size } {}
	V2_double size;
};