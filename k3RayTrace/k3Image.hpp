#ifndef K3IMAGE_H
#define K3IMAGE_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class k3Image
{
    public:
        // Constructor
        k3Image();

        // Destructor
        ~k3Image();

        // Initialization
        void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

        // Set color of a pixel
        void SetPixel(const int x, const int y, const double red, const double green, const double blue);

        // Get the final image
        void GetImage();

        // Get image's dimensions
        int GetWidth();
        int GetHeight();

    private:
        Uint32 ConvertColor(const double red, const double green, const double blue);
        void InitTexture();

    private:
        // Array to store image data
        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        // Image dimension
        int m_xSize, m_ySize;

        // SDL2 stuff
        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;
};

#endif