#include "hexagon_RGB.h"
#include "hexagon.h"

const double SQRT_2 = sqrt(2.0);
const double SQRT_3 = sqrt(3.0);


void hexagon_RGB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    Draw_Border(target, states, "RGB");
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sprite.setTexture(textureRed);
    int height = center.y - p[0].y;

    sf::Transform transRed;
    transRed.translate(center).rotate(180).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    target.draw(sprite, transRed);

    sf::Transform transGreen;
    transGreen.translate(center).rotate(60).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    sprite.setTexture(textureGreen);
    target.draw(sprite, transGreen);

    sf::Transform transBlue;
    transBlue.translate(center).rotate(-60).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    sprite.setTexture(textureBlue);
    target.draw(sprite, transBlue);

    sf::VertexArray lines(sf::LinesStrip, 7);


    for (int i = 0; i < 6; ++i) {
        float angle_rad = (60.f * i - 30.f) * (3.141592654f / 180.f);
        sf::Vector2f vertex = center + sf::Vector2f(height * cos(angle_rad), height * sin(angle_rad));
        lines[i].position = vertex;
        lines[i].color = sf::Color::Black;
    }


    lines[6] = lines[0];

    target.draw(lines, states);
}
void hexagon_RGB::updateColors(float offs){
    sf::Image image;
    image.create(256, 256);

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            image.setPixel((255 - i), 255 - j, sf::Color(255 * (1 - offs), j * (1 - offs), i * (1 - offs)));
        }
    }
    textureRed.loadFromImage(image);
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            image.setPixel(255 - i, 255 - j, sf::Color(i* (1 - offs), 255* (1 - offs), j* (1 - offs)));
        }
    }
    textureGreen.loadFromImage(image);
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            image.setPixel(255 - i, 255 - j, sf::Color(j* (1 - offs),i* (1 - offs),255* (1 - offs)));
        }
    }
    textureBlue.loadFromImage(image);
}

