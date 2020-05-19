#include <iostream>
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>

#include "include/snake.hh"

using namespace std::literals::chrono_literals;


/*
We want to have the following routine:
Setup
Draw
Input
Logic

Can't hit the walls, or the head of the body
*/

SnakeGame::SnakeGame()
{
    //resize the board to be the apprpriate size we want
    board.resize(20);
    for (auto& row : board)
    {
        row.resize(20);
    }
    headPosition[0] = 9;
    headPosition[1] = 9; 
}

void SnakeGame::Setup()
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
           // bounds of the board
           if (i == 0 || i == 19 || j == 0 || j == 19)
           {
               board[i][j] = '#';
           } 
           else
           {
               board[i][j] = ' ';
           }
        }
    }
    currentDirection = STOP;
    keepPlaying = true;
}

void SnakeGame::Draw()
{
    system("clear");
    // this needs to go into the logic method. Make all things in logic
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            std::cout << board[i][j]; 
        }
        std::cout << "\n";
    }

    std::cout << "Headposition: " << headPosition[0] << " "
        << headPosition[1] << std::endl;
    
}

void SnakeGame::Input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        currentDirection = UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        currentDirection = LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        currentDirection = DOWN;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        currentDirection = RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        keepPlaying = false;
    }
}

void SnakeGame::Logic()
{
    // analyze the user input and control the snake
    // take the older position and store it
    if (headPosition[0] == 0 || headPosition[0] == 19
        || headPosition[1] == 0 || headPosition[1] == 19)
    {
        board[headPosition[0]][headPosition[1]] = '#';
    }
    else
    {
        board[headPosition[0]][headPosition[1]] = ' ';
    }
    
    switch(currentDirection)
    {
        case UP:
        {
            if (headPosition[0]!= 0)
            {
                headPosition[0] --;
                this->gameSnake.headPosition.y --;
            }
        }
        break;
        case DOWN:
        {
            if (headPosition[0] != 19)
            {
                headPosition[0] ++;
                this->gameSnake.headPosition.y ++;
            }
        }
        break;
        case LEFT:
        {
            if (headPosition[1] != 0)
            {
                headPosition[1] --;
            }
        }
        break;
        case RIGHT:
        {
            if(headPosition[1] != 19)
            {
                headPosition[1] ++;
            }
        }
        break;
        case STOP:
        {
            // start of the game, basically do nothing
        }
    }
    board[headPosition[0]][headPosition[1]] = 'O';
}