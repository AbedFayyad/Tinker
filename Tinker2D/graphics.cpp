
//
//  graphics.cpp
//  Tinker2D
//
//  Created by Abed on 2016-06-20.
//
//

#include "graphics.hpp"

#include <SDL2/SDL.h>
#include "globals.hpp"
#include "sprite.hpp"

Graphics::Graphics() {
    
    // Create a window
    window = SDL_CreateWindow("Tinker2D",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT,
                              0);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed %s\n", SDL_GetError());
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed %s\n", SDL_GetError());
    }
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

void Graphics::draw(Sprite *sprite) {
    SDL_RenderCopy(renderer, sprite->texture, &sprite->boundingBox, &sprite->position);
}

void Graphics::update() {
    SDL_RenderPresent(renderer);
}