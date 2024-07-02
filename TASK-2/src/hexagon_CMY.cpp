
#include "hexagon_CMY.h"
#include "hexagon.h"

const double SQRT_2 = sqrt(2.0);
const double SQRT_3 = sqrt(3.0);

void hexagon_CMY::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    Draw_Border(target, states, "CMY");
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sprite.setTexture(textureCyan);
    int height = center.y - p[0].y;

    sf::Transform transCyan;
    transCyan.translate(center).rotate(180).scale(height * SQRT_3/(256.0 * SQRT_2), height/(256.0 * SQRT_2)).rotate(45);
    target.draw(sprite, transCyan);

    sf::Transform transMagenta;
    transMagenta.translate(center).rotate(60).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    sprite.setTexture(textureMagenta);
    target.draw(sprite, transMagenta);

    sf::Transform transYellow;
    transYellow.translate(center).rotate(-60).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    sprite.setTexture(textureYellow);
    target.draw(sprite, transYellow);

    sf::VertexArray lines(sf::LinesStrip, 7); // 7 points to form a closed loop

    // Define the points for the hexagon's outline
    for (int i = 0; i < 6; ++i) {
        float angle_rad = (60.f * i - 30.f) * (3.141592654f / 180.f); // Convert angle to radians
        sf::Vector2f vertex = center + sf::Vector2f(height * cos(angle_rad), height * sin(angle_rad));
        lines[i].position = vertex;
        lines[i].color = sf::Color::Black;
    }

    // Connect back to the first point to close the loop
    lines[6] = lines[0];

    // Draw the outline
    target.draw(lines, states);
}


void hexagon_CMY::updateColors(float offs)
{
    sf::Image image;
    image.create(256,256);

    // Update Cyan texture
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            int cyan =  0;
            int magenta = 255 * (255 - j) / 255.0f;
            int yellow = 255 * ((255 - i) / 255.0f);

            // Adjust colors based on offset
            cyan = cyan + (255 - cyan) * offs;
            magenta = magenta + (255 - magenta) * offs;
            yellow = yellow + (255 - yellow) * offs;

            // Ensure color components stay within bounds
            cyan = std::min(255, std::max(0, cyan));
            magenta = std::min(255, std::max(0, magenta));
            yellow = std::min(255, std::max(0, yellow));

            image.setPixel(255-i,255-j,sf::Color(cyan,magenta,yellow));
        }
    }
    textureCyan.loadFromImage(image);

    // Update Magenta texture
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            int cyan = 255 * (255 - i) / 255.0f;
            int magenta = 0;
            int yellow =  255 * (255 - j) / 255.0f;

            // Adjust colors based on offset
            cyan = cyan + (255 - cyan) * offs;
            magenta = magenta + (255 - magenta) * offs;
            yellow = yellow + (255 - yellow) * offs;

            // Ensure color components stay within bounds
            cyan = std::min(255, std::max(0, cyan));
            magenta = std::min(255, std::max(0, magenta));
            yellow = std::min(255, std::max(0, yellow));

            image.setPixel(255-i,255-j,sf::Color(cyan,magenta,yellow));
        }
    }
    textureMagenta.loadFromImage(image);

    // Update Yellow texture
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            int cyan = 255 * (255 - j) / 255.0f;
            int magenta = 255 * (255 - i) / 255.0f;
            int yellow =  0;

            // Adjust colors based on offset
            cyan = cyan + (255 - cyan) * offs;
            magenta = magenta + (255 - magenta) * offs;
            yellow = yellow + (255 - yellow) * offs;

            // Ensure color components stay within bounds
            cyan = std::min(255, std::max(0, cyan));
            magenta = std::min(255, std::max(0, magenta));
            yellow = std::min(255, std::max(0, yellow));

            image.setPixel(255-i,255-j,sf::Color(cyan,magenta,yellow));
        }
    }
    textureYellow.loadFromImage(image);
}