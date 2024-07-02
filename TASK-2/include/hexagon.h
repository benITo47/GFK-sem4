#ifndef HEXAGON_H
#define HEXAGON_H

#include "SFML/Graphics.hpp"
#include "ShareTechMono-Regular.h"
#include <numeric>
#include <iostream>

class hexagon : public sf::Drawable
{
protected:
    sf::Vector2f left_top, right_bottom, center;
    sf::Vector2f p[6]; // Kolejność punktów opisana w pliku PDF do laboratorium.
public:
    void Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom);
    void Draw_Border(sf::RenderTarget& target, sf::RenderStates states, sf::String name) const;
    bool rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const;



private:
    float d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const;
};





#endif