// Check if it has imported (lit.: if CAPP_H not defined, well, define it LOL)
#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "k3RayTrace/k3Image.hpp"
#include "k3RayTrace/scene.hpp"

class CApp
{
    public:
        CApp();

        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event *event);
        void OnLoop();
        void OnRender();
        void OnExit();

    private:
        // An instance of k3Image class (the "image" class)
        k3Image m_image;

        // The scene class's instance
        k3RT::Scene m_scene;

        // SDL2 stuff
        bool isRunning;
        SDL_Window *pWindow;
        SDL_Renderer *pRenderer;
};

#endif