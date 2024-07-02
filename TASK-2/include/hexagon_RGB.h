#ifndef HEXAGON_RGB
#define HEXAGON_RGB
#include "SFML/Graphics.hpp"
#include "hexagon.h"



class hexagon_RGB : public hexagon
{
    sf::Texture textureRed;
    sf::Texture textureGreen;
    sf::Texture textureBlue;

public:

    hexagon_RGB()
    {
        updateColors(0.0f);
    }

    void updateColors(float offs);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif