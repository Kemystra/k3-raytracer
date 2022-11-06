#include "CApp.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 320;

CApp::CApp()
{
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    pWindow = SDL_CreateWindow("RayTracer - k3mystra",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 
    WINDOW_WIDTH, WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN);

    if(pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        // Initialize an instance of image
        m_image.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, pRenderer);
        for(int x = 0; x < WINDOW_WIDTH; ++x)
        {
            for(int y = 0; y < WINDOW_HEIGHT; ++y)
            {
                double red = static_cast<double>(x ) / WINDOW_WIDTH * 255.0;
                double green = static_cast<double>(y) / WINDOW_HEIGHT * 255.0;

                m_image.SetPixel(x, y, red, green, 0.0);
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

int CApp::OnExecute()
{
    SDL_Event event;

    if(!OnInit())
    {
        return -1;
    }

    while(isRunning)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }

    OnExit();
    return 0;
}

void CApp::OnEvent(SDL_Event *event)
{
    if(event -> type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void CApp::OnLoop()
{

}

void CApp::OnRender()
{
    // Set background to white
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    // Display the image
    m_image.GetImage();

    SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
    // Tidy up SDL2
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    pWindow = NULL;
    SDL_Quit();
}