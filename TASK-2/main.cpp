//Uwaga! Co najmniej C++17!!!
//Project-> ... Properties->Configuration Properties->General->C++ Language Standard == ISO C++ 17 Standard (/std:c++17)

#include "SFML/Graphics.hpp"
#include "ShareTechMono-Regular.h"
#include <numeric>
#include <iostream>
#include <hexagon.h>
#include<hexagon_CMY.h>
#include<hexagon_HSB.h>
#include<hexagon_HSL.h>
#include<hexagon_RGB.h>
#include "slider.h"

//Tak – dobrze państwo widzą – TO jest zmienna globalna! Czytanie i przetwarzanie fontów w SFML jest bardzo kosztowne. Dlatego zrobimy to raz. 
//Co nie zmienia faktu, że można by to zrobić bez zmiennej globalnej i to całkiem ładnie. Jak? To już dla Państwa :-)
std::shared_ptr<sf::Font> font;

int main(){

 sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
 
 hexagon_RGB h_RGB;
 hexagon_CMY h_CMY;
 hexagon_HSL h_HSL;
 hexagon_HSB h_HSB;
 slider Slider;

 sf::Clock frame_clock, around_half_secound_clock;
 sf::Int64 mean_frames_time = 0;
 std::vector<sf::Int64> frame_times;
 sf::Text text;

 font = std::make_shared<sf::Font>();
 font->loadFromMemory(&(ShareTechMono_Regular_ttf[0]), ShareTechMono_Regular_ttf.size());
 text.setFont(*font);
 text.setCharacterSize(21);
 text.setFillColor(sf::Color::Black);

 //Nie mogę uniknąć tych "magic numbers" bo bym zdradził w ten sposób co ma być w sf::Event::Resize. A tego byśmy nie chcieli - prawda? :-D
 text.setPosition(10, 10);
 h_RGB.Set_Borders(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(300.0f,294.0f));
 h_CMY.Set_Borders(sf::Vector2f(300.0f, 0.0f), sf::Vector2f(600.0f, 294.0f));
 h_HSL.Set_Borders(sf::Vector2f(0.0f, 294.0f), sf::Vector2f(300.0f, 588.0f));
 h_HSB.Set_Borders(sf::Vector2f(300.0f, 294.0f), sf::Vector2f(600.0f, 588.0f));
 Slider.SetBorder(sf::Vector2f(700.0f, 15.0), sf::Vector2f(750.0f, 450.0f));
 text.setPosition(700.0, 450.0f);

 float slider_width = 100.0f;

    around_half_secound_clock.restart();

 while (window.isOpen())
 {
  sf::Event event;
  window.clear(sf::Color::White);

  frame_clock.restart(); // Start pomiaru czasu.

  while (window.pollEvent(event))
  {
      if (event.type == sf::Event::Closed) window.close();

      if(event.type == sf::Event::Resized)
      {
          unsigned int window_width = event.size.width;
          unsigned int window_height = event.size.height;

          // dont let the window get too small
          if (window_width < 800 || window_height < 600) {
              window.setView(sf::View(sf::FloatRect(0, 0, 800, 600)));
              window.setSize(sf::Vector2u(800, 600));
          } else {
              float borderSize = window_height > (window_width - slider_width) ? (window_width - slider_width) / 2 : window_height / 2;
              h_RGB.Set_Borders(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(borderSize, borderSize));
              h_CMY.Set_Borders(sf::Vector2f(borderSize, 0.0f), sf::Vector2f(2 * borderSize, borderSize));
              h_HSL.Set_Borders(sf::Vector2f(0.0f, borderSize), sf::Vector2f(borderSize, 2 * borderSize));
              h_HSB.Set_Borders(sf::Vector2f(borderSize, borderSize), sf::Vector2f(2 * borderSize, 2 * borderSize));
              Slider.SetBorder(sf::Vector2f(2 * borderSize + 100.0f, 20.0f), sf::Vector2f(2 * borderSize + 150.0f, 2 * borderSize - 150.0f));
              text.setPosition(2 * borderSize + 100.0f, 2 * borderSize - 150.0f);
              window.setView(sf::View(sf::FloatRect(0, 0, window_width, window_height)));
          }


          window.clear();
          window.draw(h_RGB);
          window.draw(h_CMY);
          window.draw(h_HSL);
          window.draw(h_HSB);
          window.draw(text);
          window.display();
      }
      if (Slider.checkIfMoved(event)) {


          h_RGB.updateColors(Slider.GetSliderValue());
          h_CMY.updateColors(Slider.GetSliderValue());
          h_HSL.updateColors(Slider.GetSliderValue());
          h_HSB.updateColors(Slider.GetSliderValue());

          window.draw(h_RGB);
          window.draw(h_CMY);
          window.draw(h_HSL);
          window.draw(h_HSB);
          window.draw(Slider);
          window.display();
      }
  }

  window.draw(h_RGB);
  window.draw(h_CMY);
  window.draw(h_HSL);
  window.draw(h_HSB);
  window.draw(Slider);

     // Pewnie tu gdzieś wypadało by dorysować jeszcze suwaczek...
  text.setString(std::to_string(mean_frames_time)+ "us");

  window.draw(text);

  // Pomiar czasu uśrednimy w okresie około 1/2 sekundy.
  frame_times.push_back(frame_clock.getElapsedTime().asMicroseconds());
  if (around_half_secound_clock.getElapsedTime().asSeconds() >= 0.5f && frame_times.size() >=1)
  {
      mean_frames_time = (sf::Int64)((float)std::reduce(frame_times.begin(), frame_times.end()) / (float)frame_times.size());
      frame_times.clear();
      around_half_secound_clock.restart();
  }

  frame_clock.restart(); // Stop pomiaru czasu.
  window.display();
 }

 //Hmmm ... :-/
 font.reset();
 
 return 0;
}
