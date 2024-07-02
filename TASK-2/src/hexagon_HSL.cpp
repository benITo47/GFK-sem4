#include "hexagon_HSL.h"
#include "hexagon.h"
const double SQRT_2 = sqrt(2.0);
const double SQRT_3 = sqrt(3.0);

sf::Color hexagon_HSL::HSLtoRGB(float hue, float saturation, float lightness) {
    float chroma = (1 - std::abs(2 * lightness - 1)) * saturation;
    float huePrime = hue / 60;
    float x = chroma * (1 - std::abs(fmod(huePrime, 2) - 1));
    float m = lightness - chroma / 2;

    float r, g, b;
    if (huePrime >= 0 && huePrime < 1) {
        r = chroma;
        g = x;
        b = 0;
    } else if (huePrime >= 1 && huePrime < 2) {
        r = x;
        g = chroma;
        b = 0;
    } else if (huePrime >= 2 && huePrime < 3) {
        r = 0;
        g = chroma;
        b = x;
    } else if (huePrime >= 3 && huePrime < 4) {
        r = 0;
        g = x;
        b = chroma;
    } else if (huePrime >= 4 && huePrime < 5) {
        r = x;
        g = 0;
        b = chroma;
    } else { // huePrime >= 5 && huePrime < 6
        r = chroma;
        g = 0;
        b = x;
    }

    int red = static_cast<int>((r + m) * 255);
    int green = static_cast<int>((g + m) * 255);
    int blue = static_cast<int>((b + m) * 255);

    return sf::Color(red, green, blue);
}


void hexagon_HSL::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Draw_Border(target, states, "HSL");
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sprite.setTexture(textureHue);
    int height = center.y - p[0].y;

    sf::Transform transHue;
    transHue.translate(center).rotate(180).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    target.draw(sprite, transHue);

    sf::Transform transSaturation;
    transSaturation.translate(center).rotate(60).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    sprite.setTexture(textureSaturation);
    target.draw(sprite, transSaturation);

    sf::Transform transLevel;
    transLevel.translate(center).rotate(-60).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    sprite.setTexture(textureLevel);
    target.draw(sprite, transLevel);

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


void hexagon_HSL::updateColors(float offs)
{

    sf::Image image;
    image.create(256,256);


    for(int i = 0; i<256; i++)
    {
        for(int j =0; j < 256; j++)
        {
            float Hue = 360.0f; // Hue ranges from 0 to 360
            float Saturation = (j) / 255.0f;   // Saturation ranges from 0 to 1
            float Level = (i/ 255.0f) * (1 - offs); // Lightness ranges from 0 to 1
            image.setPixel(255-i,255-j,sf::Color(HSLtoRGB(Hue,Saturation,Level)));
        }
    }
    textureHue.loadFromImage(image);


    for(int i = 0; i<256; i++)
    {
        for(int j =0; j < 256; j++)
        {
            float Hue = 360.0f * (i) / 255.0f; // Hue ranges from 0 to 360
            float Saturation = 1 ; // Saturation ranges from 0 to 1
            float Level = (j) / 255.0f * (1 - offs);  // Lightness ranges from 0 to 1
            image.setPixel(255-i,255-j,sf::Color(HSLtoRGB(Hue,Saturation,Level)));
        }
    }
    textureSaturation.loadFromImage((image));
    for(int i = 0; i<256; i++)
    {
        for(int j =0; j < 256; j++)
        {
            float Hue = 360.0f * j / 255.0f; // Hue ranges from 0 to 360
            float Saturation = i / 255.0f;   // Saturation ranges from 0 to 1
            float Level = 1 * (1 - offs); // Lightness ranges from 0 to 1
            image.setPixel(255-i,255-j,sf::Color(HSLtoRGB(Hue,Saturation,Level)));
        }
    }
    textureLevel.loadFromImage(image);

}