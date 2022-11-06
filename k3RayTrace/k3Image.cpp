#include "k3Image.hpp"

// Default constructor
k3Image::k3Image()
{
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = NULL;
}

// Destructor
k3Image::~k3Image()
{
    // Detect if it has been declared
    // If SDL_DestroyTexture is called with NULL texture
    // bad stuff happens
    if(m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);
}

// Initializer
void k3Image::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer)
{
    // Resize image array
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    // Store dimensions
    m_xSize = xSize;
    m_ySize = ySize;

    // Store pointer to the renderer
    m_pRenderer = pRenderer;

    // Initialize texture
    InitTexture();
}

void k3Image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}

void k3Image::GetImage()
{
    // Allocate memory for a pixel buffer
    Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];

    // Clear pixel buffer
    // AKA: setting all values at pointer tempPixels to 0
    // to avoid reading garbage data
    memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

    for(int x = 0; x < m_xSize; ++x)
    {
        for(int y = 0; y < m_ySize; ++y)
        {
            // An elegant way of converting coordinates into linear index
            tempPixels[(y*m_xSize) + x] = ConvertColor(m_rChannel.at(x).at(y),
                                                    m_gChannel.at(x).at(y),
                                                    m_bChannel.at(x).at(y));
        }
    }

    // Update texture with the buffer
    SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

    // Delete buffer
    delete[] tempPixels;

    // Copy texture to renderer
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;

    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

// Return dimensions
int k3Image::GetWidth()
{
    return m_xSize;
}

int k3Image::GetHeight()
{
    return m_ySize;
}

void k3Image::InitTexture()
{
    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    // delete previous texture
    if(m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);

    // Create texture to store the image
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

Uint32 k3Image::ConvertColor(const double red, const double green, const double blue)
{
    // Convert to unsigned int
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
    #else
        Uint32 pixelColor = (255 << 24) + (b << 16) + (g << 8) + r;
    #endif

    return pixelColor;
}