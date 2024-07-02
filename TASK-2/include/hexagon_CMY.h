#ifndef HEXAGON_CMY
#define HEXAGON_CMY

#include "SFML/Graphics.hpp"
#include "hexagon.h"
#include <algorithm>



class hexagon_CMY : public hexagon
{
    sf::Texture textureCyan;
    sf::Texture textureMagenta;
    sf::Texture textureYellow;
public:

    hexagon_CMY()
    {
        updateColors(0.0f);
    }

    void updateColors(float offs);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif