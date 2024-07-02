#ifndef HEXAGON_HSL
#define HEXAGON_HSL

#include "SFML/Graphics.hpp"
#include "hexagon.h"

class hexagon_HSL : public hexagon
{
    sf::Texture textureHue;
    sf::Texture textureSaturation;
    sf::Texture textureLevel;
public:

    hexagon_HSL()
    {
        updateColors(0.0f);
    }

    void updateColors(float offs);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Color HSLtoRGB(float hue, float saturation, float lightness);
};

#endif