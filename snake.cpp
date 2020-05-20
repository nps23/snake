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
    
    // make sure the snake is popualated with at least one element
    this->gameSnake.snake.resize(1);
    this->gameSnake.headPosition.x = 9;
    this->gameSnake.headPosition.y = 9;
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

    std::cout << "Headposition: " << this->gameSnake.headPosition.x << " "
        << this->gameSnake.headPosition.y << std::endl;
    
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
    int& x_head_position = this->gameSnake.headPosition.x;
    int& y_head_position = this->gameSnake.headPosition.y;
    // analyze the user input and control the snake
    // take the older position and store it
    if (x_head_position == 0 || x_head_position == 19
        || y_head_position == 0 || y_head_position == 19)
    {
        board[x_head_position][y_head_position] = '#';
    }
    else
    {
        board[x_head_position][y_head_position] = ' ';
    }
    
    switch(currentDirection)
    {
        case UP:
        {
            if (y_head_position != 0)
            {
                y_head_position --;
            }
        }
        break;
        case DOWN:
        {
            if (y_head_position != 19)
            {
                y_head_position ++;
            }
        }
        break;
        case LEFT:
        {
            if (x_head_position!= 0)
            {
                x_head_position --;
            }
        }
        break;
        case RIGHT:
        {
            if(x_head_position != 19)
            {
                x_head_position ++;
            }
        }
        break;
        case STOP:
        {
            // start of the game, basically do nothing
        }
    }
    board[x_head_position][y_head_position] = 'O';
}