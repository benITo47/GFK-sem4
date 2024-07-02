#ifndef LAB2_SLIDER_H
#define LAB2_SLIDER_H

#include "SFML/Graphics.hpp"
#include "ShareTechMono-Regular.h"
#include <iostream>

class slider : public sf::Drawable {

public:
    sf::Vector2f upperLeftCorner;
    sf::Vector2f lowerRightCorner;
    sf::Vector2f sliderPosition;


    bool isDragging;

    slider() : isDragging(false) {}

    void SetBorder(sf::Vector2f upper_left_corner, sf::Vector2f lower_right_corner);
    // Calculate slider value between 0.0-1.0
    float GetSliderValue() ;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool checkIfMoved(sf::Event event);
};
#endif //LAB2_SLIDER_H
