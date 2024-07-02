#include "hexagon_HSB.h"
#include "hexagon.h"
const double SQRT_2 = sqrt(2.0);
const double SQRT_3 = sqrt(3.0);

void hexagon_HSB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Draw_Border(target, states, "HSB");
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

    sf::Transform transBrightness;
    transBrightness.translate(center).rotate(-60).scale(height * SQRT_3 / (256.0 * SQRT_2), height / (256.0 * SQRT_2)).rotate(45);
    sprite.setTexture(textureBrigthnes);
    target.draw(sprite, transBrightness);

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

sf::Color hexagon_HSB::HSBtoRGB(float hue, float saturation, float brightness) {
    int i;
    float f, p, q, t;
    float r, g, b;

    if (saturation == 0) {
        // Achromatic (gray)
        r = g = b = brightness;
    } else {
        hue /= 60; // sector 0 to 5
        i = static_cast<int>(floor(hue));
        f = hue - i; // factorial part of hue
        p = brightness * (1 - saturation);
        q = brightness * (1 - saturation * f);
        t = brightness * (1 - saturation * (1 - f));

        switch (i) {
            case 0:
                r = brightness;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = brightness;
                b = p;
                break;
            case 2:
                r = p;
                g = brightness;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = brightness;
                break;
            case 4:
                r = t;
                g = p;
                b = brightness;
                break;
            case 6:
                r = brightness;
                g = t;
                b = p;
                break;
            default: // case 5:
                r = brightness;
                g = p;
                b = q;
                break;

        }
    }

    return sf::Color(static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(b * 255));
}

void hexagon_HSB::updateColors(float offs)
{
    sf::Image image;
    image.create(256,256);


    for(int i = 0; i<256; i++)
    {
        for(int j =0; j < 256; j++)
        {
            float Hue = 360.0f; // Hue ranges from 0 to 360
            float Saturation = (j) / 255.0f;   // Saturation ranges from 0 to 1
            float Brightness = (i/ 255.0f) * (1 - offs); // Lightness ranges from 0 to 1
            image.setPixel(255-i,255-j,sf::Color(HSBtoRGB(Hue,Saturation,Brightness)));
        }
    }
    textureHue.loadFromImage(image);


    for(int i = 0; i<256; i++)
    {
        for(int j =0; j < 256; j++)
        {
            float Hue = 360.0f * (i) / 255.0f; // Hue ranges from 0 to 360
            float Saturation = 1 ; // Saturation ranges from 0 to 1
            float Brightness = (j) / 255.0f * (1 - offs); // Lightness ranges from 0 to 1
            image.setPixel(255-i,255-j,sf::Color(HSBtoRGB(Hue,Saturation,Brightness)));
        }
    }
    textureSaturation.loadFromImage((image));
    for(int i = 0; i<256; i++)
    {
        for(int j =0; j < 256; j++)
        {
            float Hue = 360.0f * j / 255.0f; // Hue ranges from 0 to 360
            float Saturation = i / 255.0f;   // Saturation ranges from 0 to 1
            float Brightness = 1 * (1 - offs); // Lightness ranges from 0 to 1
            image.setPixel(255-i,255-j,sf::Color(HSBtoRGB(Hue,Saturation,Brightness)));
        }
    }
    textureBrigthnes.loadFromImage(image);

}