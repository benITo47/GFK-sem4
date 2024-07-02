

#include "slider.h"



void slider::SetBorder(sf::Vector2f upper_left_corner, sf::Vector2f lower_right_corner) {
    upperLeftCorner = upper_left_corner;
    lowerRightCorner = lower_right_corner;

    sliderPosition.x = upper_left_corner.x + (lower_right_corner.x - upper_left_corner.x) / 2;
    sliderPosition.y = lower_right_corner.y;
}

// Calculate slider value between 0.0-1.0
float slider::GetSliderValue() {
    float height = lowerRightCorner.y - upperLeftCorner.y;
    float sliderHeight = lowerRightCorner.y - sliderPosition.y;
    float sliderValue = sliderHeight / height;

    return sliderValue;
}

void slider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Calculate slider dimensions



    sf::VertexArray gradient(sf::Quads,4);

    gradient[0].position = sf::Vector2f(upperLeftCorner.x, upperLeftCorner.y);
    gradient[1].position = sf::Vector2f(lowerRightCorner.x, upperLeftCorner.y);
    gradient[2].position = sf::Vector2f(lowerRightCorner.x, lowerRightCorner.y);
    gradient[3].position = sf::Vector2f(upperLeftCorner.x, lowerRightCorner.y);

    gradient[0].color = sf::Color::Black;
    gradient[1].color = sf::Color::Black;
    gradient[2].color = sf::Color::White;
    gradient[3].color = sf::Color::White;


    sf::VertexArray lines(sf::LinesStrip, 5); // Change to LinesStrip and adjust size

for(int i =0; i < 5; i++) {
    lines[i].position = gradient[i%4].position;

    lines[i].color = sf::Color::Black;
}
    target.draw(gradient, states);
    target.draw(lines,states);

}

bool slider::checkIfMoved(sf::Event event) {
    // Check if the event is a mouse button press
    if (event.type == sf::Event::MouseButtonPressed) {
        // Check if the mouse button press occurred within the bounds of the slider
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

            // Check if the mouse position is within the bounds of the slider
            if (mousePos.x >= upperLeftCorner.x && mousePos.x <= lowerRightCorner.x &&
                mousePos.y >= upperLeftCorner.y && mousePos.y <= lowerRightCorner.y) {
                // Start dragging the slider knob
                isDragging = true;
                // Calculate new position for the slider knob based on mouse position
                sliderPosition.y = mousePos.y;
                // Ensure the knob stays within the bounds of the slider
                sliderPosition.y = std::max(upperLeftCorner.y, sliderPosition.y);
                sliderPosition.y = std::min(lowerRightCorner.y, sliderPosition.y);

                // Return true to indicate that the slider knob has been moved
                return true;
            }
        }
    }
        // Check if the event is a mouse button release
    else if (event.type == sf::Event::MouseButtonReleased) {
        // Stop dragging the slider knob
        isDragging = false;
    }
        // Check if the event is a mouse movement (dragging)
    else if (event.type == sf::Event::MouseMoved) {
        // Check if the mouse is currently dragging the slider knob
        if (isDragging) {
            // Update the slider position based on the mouse movement
            sliderPosition.y = event.mouseMove.y;
            // Ensure the knob stays within the bounds of the slider
            sliderPosition.y = std::max(upperLeftCorner.y, sliderPosition.y);
            sliderPosition.y = std::min(lowerRightCorner.y, sliderPosition.y);

            // Return true to indicate that the slider knob has been moved
            return true;
        }
    }

    // Return false if the knob has not been moved
    return false;
}