#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/snake.hh"
#include <thread>

#include "include/sandbox.hh"

using namespace std::literals::chrono_literals;

int main(int argc, char* argv[])
{
    switch(argc)
    {
        case 1:
        {
            SnakeGame game;
            game.Setup();
            while(game.keepPlaying)
            {
                game.Draw();
                game.Input();
                game.Logic();
                std::this_thread::sleep_for(0.05s);
            }
        } break;
        case 2: Sandbox::Debug(); break;
        case 3: Sandbox::Test(); break;
    }

}

int TEST_SFML()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;

}
