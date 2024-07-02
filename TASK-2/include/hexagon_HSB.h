#ifndef HEXAGON_HSB
#define HEXAGON_HSB

#include "SFML/Graphics.hpp"
#include "hexagon.h"

class hexagon_HSB : public hexagon
{
    sf::Texture textureHue;
    sf::Texture textureSaturation;
    sf::Texture textureBrigthnes;
public:
    hexagon_HSB()
    {
        updateColors(0.0f);
    }

    void updateColors(float offs);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Color HSBtoRGB(float hue, float saturation, float brightness);
};



#endif