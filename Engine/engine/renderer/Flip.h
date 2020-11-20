#pragma once

enum class Flip {
    NONE = 0, // SDL_FLIP_NONE
    HORIZONTAL = 1, // SDL_FLIP_HORIZONTAL
    VERTICAL = 2, // SDL_FLIP_VERTICAL
    BOTH = 3 // SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
};