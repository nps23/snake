#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/snake.hh"
#include <thread>

using namespace std::literals::chrono_literals;

int main()
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

// bool keepPlaying = true;
// while(keepPlaying)
// {
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
//     {
//         std::cout << "You pressed E! Would you like to continure?";
//         char input;
//         std::cin>>input;
//         if (input == 'n')
//         {
//             keepPlaying = false;
//         }
//     }
// }  