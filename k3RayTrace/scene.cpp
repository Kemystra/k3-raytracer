#include "scene.hpp"

// Constructor
k3RT::Scene::Scene()
{

}

// Do rendering
bool k3RT::Scene::Render(k3Image &outputImage)
{
    // get output image's dimensions
    int imageWidth = outputImage.GetWidth();
    int imageHeight = outputImage.GetHeight();

    // Create color variations
    for(int x = 0; x < imageWidth; x++)
    {
        for(int y = 0; y < imageHeight; y++)
        {
            double red = static_cast<double>(x) / static_cast<double>(imageWidth) * 255.0;
            double green = static_cast<double>(y) / static_cast<double>(imageHeight) * 255.0;

            outputImage.SetPixel(x, y, red, green, 5.0);
        }
    }

    return true;
}