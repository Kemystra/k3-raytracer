#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "k3Image.hpp"

class Scene;

namespace k3RT
{
    class Scene
    {
        public:
            // Default constructor
            Scene();
    
            // Do rendering
            bool Render(k3Image &outputImage);
            
        // Private functions
        //private:
    
        // Private members
        //private:
        
    };
}

#endif