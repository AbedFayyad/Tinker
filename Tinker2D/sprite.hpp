//
//  sprite.hpp
//  Tinker2D
//
//  Created by Abed on 2016-06-20.
//
//

#ifndef sprite_hpp
#define sprite_hpp

#include <SDL2/SDL.h>

class Sprite {
public:
    Sprite();
    Sprite(SDL_Texture *texture, SDL_Rect *boundingBox, SDL_Rect *position);
    ~Sprite();
    
    SDL_Texture *texture;
    SDL_Rect boundingBox;
    SDL_Rect position;
};

#endif /* sprite_hpp */
