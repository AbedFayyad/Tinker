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
        
    bool shouldQuit = false;
    SDL_Event event;
    
    int lastUpdateTime = SDL_GetTicks();
    int currentTime;
    int elapsedTime;
    
    // TODO: remove me
    (void) lastUpdateTime;
    (void) currentTime;
    (void) elapsedTime;
    (void) FPS;
    (void) MS_PER_S;
    (void) MAX_FRAME_TIME;
    
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
        else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) NULL; // Move left
        else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) NULL; // Move right
        
        // Simulate physics
        
        // Redraw graphics
        graphics.draw();
    }
}