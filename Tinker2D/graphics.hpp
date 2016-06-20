//
//  graphics.hpp
//  Tinker2D
//
//  Created by Abed on 2016-06-20.
//
//

#ifndef graphics_hpp
#define graphics_hpp

class Sprite;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Graphics {
public:
    Graphics();
    ~Graphics();
    
    void clear();
    void draw(Sprite *sprite);
    void update();
    SDL_Renderer *renderer;
private:
    SDL_Window *window;
};

#endif /* graphics_hpp */
