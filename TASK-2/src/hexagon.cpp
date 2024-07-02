#include "SFML/Graphics.hpp"
#include "ShareTechMono-Regular.h"
#include <numeric>
#include <iostream>
#include "hexagon.h"

//Trochę matematyki jeszcze nikomu nie zaszkodziło. Więc dwie kolejne metody to czysta matematyka.



float hexagon::d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const
{
    float A = p0.y - p1.y;
    float B = p1.x - p0.x;
    float C = p0.x * (p1.y - p0.y) - p0.y * (p1.x - p0.x);

    return 2 * ((A * p.x + B * p.y + C) / sqrt(A * A + B * B)) / sqrt(3.0f);
}

bool hexagon::rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const
{
    float L = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    sf::Vector2f p3(0.5f * (p0.x - p1.x) + 0.5f * sqrt(3.0f) * (p1.y - p0.y) + p0.x, 0.5f * sqrt(3.0f) * (p0.x - p1.x) - 0.5f * (p1.y - p0.y) + p0.y);

    beta = -d_coefficient(p0, p1, p) / L;
    alpha = d_coefficient(p0, p3, p) / L;

    if ((alpha > 1.0f) || (beta > 1.0f) || (alpha < 0.0f) || (beta < 0.0f)) return false; else return true;
}

void hexagon::Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom)
{
    left_top = _left_top;
    right_bottom = _right_bottom;
    float a = ((right_bottom.y - left_top.y) / 2.0f + 0.5f) - 20.0f;
    center = left_top + sf::Vector2f((right_bottom.x - left_top.x) / 2.0f + 0.5f, (right_bottom.y - left_top.y) / 2.0f + 0.5f + 10);

    p[0] = center - sf::Vector2f( 0.0f, a);
    p[1] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[2] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);
    p[3] = center + sf::Vector2f(0.0f, a);
    p[4] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[5] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);
}

void hexagon::Draw_Border(sf::RenderTarget& target, sf::RenderStates states,  sf::String name) const {

    float padding{10.0f};
    // Calculate the size of the square border
    float border_width = (right_bottom.x - left_top.x - 2 * padding);
    float border_height = (right_bottom.y - left_top.y- 2 * padding);


    sf::Vector2f border_position(left_top.x + padding, left_top.y + padding);

    // Draw the square border
    sf::RectangleShape border(sf::Vector2f(border_width, border_height));
    border.setPosition(border_position);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(3.0f);
    border.setOutlineColor(sf::Color::Black);
    target.draw(border, states);
    // Draw the text

    extern std::shared_ptr<sf::Font> font;
    sf::Text text(name.substring(0, 3), *font, 16); // Take only the first three characters
    text.setOrigin(0.f, 0.f); // Set origin to the upper-left corner
    text.setPosition(border_position.x, border_position.y); // Adjust position to left upper corner
    text.setFillColor(sf::Color::Black);
    target.draw(text, states);

    std::array<sf::Text, 3> rhombus_letters;
    for (int i = 0; i < 3; i++) {
        sf::FloatRect label_bounding_box = rhombus_letters[i].getLocalBounds();
        rhombus_letters[i].setOrigin(label_bounding_box.width / 2, label_bounding_box.height / 2);

        sf::Vector2f position = p[i * 2];

        if (i == 0) {
            position.y -= 25.0f;
        }

        rhombus_letters[i].setPosition(position);
        rhombus_letters[i].setFont(*font);
        rhombus_letters[i].setCharacterSize(21);
        rhombus_letters[i].setFillColor(sf::Color::Black);
        rhombus_letters[i].setString(name[i]);
        target.draw(rhombus_letters[i], states);
    }


}