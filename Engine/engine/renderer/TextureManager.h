#pragma once

#include <unordered_map> // std::unordered_map
#include <cstdint> // std::uint32_t

#include "utils/math/Vector2.h"
#include "renderer/Color.h"
#include "renderer/Flip.h"
#include "renderer/AABB.h"
#include "renderer/Renderer.h"

namespace engine {

// Default color of renderer window
#define DEFAULT_RENDERER_COLOR WHITE
// Default color of renderer objects
#define DEFAULT_RENDER_COLOR BLACK

struct Texture;

enum class TextureAccess : int {
	STATIC = 0, // SDL_TEXTUREACCESS_STATIC = 0
	STREAMING = 1, // SDL_TEXTUREACCESS_STREAMING = 1
	TARGET = 2 // SDL_TEXTUREACCESS_TARGET = 2
};

enum class PixelFormat : std::uint32_t {
	ARGB8888 = 372645892 // SDL_PIXELFORMAT_ARGB8888 = 372645892
};

class TextureManager {
private:
public:
	static void Load(const char* texture_key, const char* texture_path);

	static Texture CreateTexture(const Renderer& renderer, PixelFormat format, TextureAccess texture_access, const V2_int& size);

	static void RenderTexture(const Renderer& renderer, const Texture& texture, const AABB* source = nullptr, const AABB* destination = nullptr);

	// Return the location of a 4 byte integer value containg the RGBA32 color of the pixel on an SDL_Surface or SDL_Texture.
	static std::uint32_t& GetTexturePixel(void* pixels, const V2_int& position, const int pitch);

	static Color GetDefaultRendererColor();
	static void SetDrawColor(const Color& color);

	static void DrawPoint(const V2_int& point, const Color& color);
	static void DrawLine(const V2_int& origin, const V2_int& destination, const Color& color);
	static void DrawSolidRectangle(const V2_int& position, const V2_int& size, const Color& color);
	static void DrawRectangle(const V2_int& position, const V2_int& size, const Color& color);
	static void DrawRectangle(const V2_int& position, const V2_int& size, const double rotation, const Color& color, V2_double* center_of_rotation = nullptr);
	static void DrawRectangle(const char* texture_key, const V2_int& src_position, const V2_int& src_size, const V2_int& dest_position, const V2_int& dest_size, Flip flip = Flip::NONE, V2_double* center_of_rotation = nullptr, double angle = 0.0);
	static void DrawCircle(const V2_int& center, const int radius, const Color& color);
	static void DrawSolidCircle(const V2_int& center, const int radius, const Color& color);

	static void SetDrawColor(const Renderer& renderer, const Color& color);
	static void DrawPoint(const Renderer& renderer, const V2_int& point, const Color& color);
	static void DrawLine(const Renderer& renderer, const V2_int& origin, const V2_int& destination, const Color& color);

	friend class Image;
	static void Clean();
private:
	static void RemoveTexture(const char* texture_key);
	static Texture GetTexture(const char* texture_key);
	static std::unordered_map<std::size_t, Texture> texture_map_;
};

} // namespace engine