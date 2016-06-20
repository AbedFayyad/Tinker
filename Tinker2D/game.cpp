//
//  game.cpp
//  Tinker2D
//
//  Created by Abed on 2016-06-20.
//
//

#include "game.hpp"

#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "input.hpp"
#include "sprite.hpp"

namespace {
    const int FPS = 60;
    const int MS_PER_S = 1000;
    const int MAX_FRAME_TIME = MS_PER_S / FPS;
}

Game::Game() {
    
    // Initialize SDL subsystems
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    } else {
        gameLoop();
    }
}

Game::~Game() {
    
    // Clean up all initialized SDL subsystems
    SDL_Quit();
}

void Game::gameLoop() {
    Graphics graphics;
    Input input;
    
    Sprite sprite;
    sprite.boundingBox.x = 0;
    sprite.boundingBox.y = 0;
    sprite.boundingBox.w = 16;
    sprite.boundingBox.h = 16;
    sprite.position.x = 100;
    sprite.position.y = 100;
    sprite.position.w = 16;
    sprite.position.h = 16;
    sprite.texture = SDL_CreateTextureFromSurface(graphics.renderer, SDL_LoadBMP("fuck.bmp"));
        
    bool shouldQuit = false;
    SDL_Event event;
    
    int lastUpdateTime = SDL_GetTicks();
    int currentTime;
    int elapsedTime;
    
    // Each iteration of this loop is a single frame
    while (!shouldQuit) {
        input.beginNewFrame();
        
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (!event.key.repeat) input.keyDownEvent(event);
                    break;
                case SDL_KEYUP:
                    input.keyUpEvent(event);
                    break;
                case SDL_QUIT:
                    shouldQuit = true;
                    break;
            }
        }
        
        // Handle keystrokes
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) shouldQuit = true;
        else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) sprite.position.x -= 1;
        else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) sprite.position.x += 1;
        
        // Simulate physics
        
        // Redraw graphics
        graphics.clear();
        graphics.draw(&sprite);
        graphics.update();
    }
}