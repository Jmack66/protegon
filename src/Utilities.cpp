#include "Utilities.h"

#include "Vec2D.h"
#include "SDL.h"

namespace Util {
	double truncate(double value, int digits) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(digits) << value;
		return std::stod(stream.str());
	}

	SDL_Rect RectFromVec(const Vec2D& position, const Vec2D& size) {
		return SDL_Rect{ static_cast<int>(round(position.x)), static_cast<int>(round(position.y)), static_cast<int>(round(size.x)), static_cast<int>(round(size.y)) };
	}
}