#include <iostream>
#include <vector>
#include <thread>
#include <random>
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
    gameSnake.snake.resize(3);
    gameSnake.snake[0].x = 9;
    gameSnake.snake[0].y = 9;
    
    gameSnake.snake[1].x = 9;
    gameSnake.snake[1].y = 10;

    gameSnake.snake[2].x = 9;
    gameSnake.snake[2].y = 11;

    fruit1 = new int[2];
    fruit2 = new int[2];
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
    // debug
    //currentDirection = DOWN;
    keepPlaying = true;

    // set up some fruit on the board. Two at a time
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 19);
    
    fruit1[0] = distribution(generator);
    fruit1[1] = distribution(generator);

    fruit2[0] = distribution(generator);
    fruit2[1] = distribution(generator);

    while(fruit1[0] == fruit2[0] || fruit1[1] == fruit2[1])
    {
        fruit2[0] = distribution(generator);
        fruit2[1] = distribution(generator);
    }

    board[fruit1[0]][fruit1[1]] = 'X';
    board[fruit2[0]][fruit2[1]] = 'X';
}



void SnakeGame::Draw()
{
    system("clear");
    // this needs to go into the logic method.
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            std::cout << board[i][j]; 
        }
        std::cout << "\n";
    }

    std::cout << "Headposition: " << gameSnake.snake[0].x << " "
        << gameSnake.snake[0].y << std::endl;
    std::cout << "Fruit1 at position: " << fruit1[0] << " " << fruit1[1] << std::endl;
    std::cout << "Fruit2 at position: " << fruit2[0] << " " << fruit2[1] << std::endl;
    std::cout << "Snake size: " << gameSnake.snake.size() << std::endl; 
    
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
    int& snake_head_col_position = gameSnake.snake[0].x;
    int& snake_head_row_position = gameSnake.snake[0].y;

    // analyze the user input and control the snake
    
    // reset the board
    for (int i = 0; i < gameSnake.snake.size(); ++i)
    {
        if (gameSnake.snake[i].x == 0 || gameSnake.snake[i].x == 19 ||
            gameSnake.snake[i].y == 0 || gameSnake.snake[i].y == 19)
            {
                board[gameSnake.snake[i].y][gameSnake.snake[i].x] = '#';
            }
        else
        {
            board[gameSnake.snake[i].y][gameSnake.snake[i].x] = ' ';
        }
        
    }
    
    switch(currentDirection)
    {
        case UP:
        {           
            // make sure the snake doesn't 'fall into' itself
            if (gameSnake.snake[0].y > gameSnake.snake[1].y)
            {
                keepPlaying = false;
                break;
            }
            if (snake_head_row_position != 0)
            {
                // move the head position
                snake_head_row_position --;
                for (int i = 1; i < gameSnake.snake.size(); ++i)
                {
                    if (gameSnake.snake[i].x == snake_head_col_position)
                    {
                        gameSnake.snake[i].y --;
                    }
                    else if (gameSnake.snake[i].x > snake_head_col_position)
                    {
                        gameSnake.snake[i].x --;
                    }
                    else if (gameSnake.snake[i].x < snake_head_col_position)
                    {
                        gameSnake.snake[i].x ++;
                    }
                }
            }
        }
        break;
        case DOWN:
        {
            if (gameSnake.snake[0].y < gameSnake.snake[1].y)
            {
                keepPlaying = false;
                break;
            }
            if (snake_head_row_position != 19)
            {
                snake_head_row_position ++;
                for (int i = 1; i < gameSnake.snake.size(); ++i)
                {
                    if (gameSnake.snake[i].x == snake_head_col_position) // we can shift them if they are on the same plane
                    {
                        gameSnake.snake[i].y ++;
                    }
                    else if (gameSnake.snake[i].x > snake_head_col_position)
                    {
                        gameSnake.snake[i].x --;
                    }
                    else if (gameSnake.snake[i].x < snake_head_col_position)
                    {
                        gameSnake.snake[i].x ++;
                    }
                }
            }
        }
        break;
        case LEFT:
        {
            if (gameSnake.snake[0].x > gameSnake.snake[1].x)\
            {
                keepPlaying = false;
                break;
            }
            if (snake_head_col_position!= 0)
            {
                snake_head_col_position --;
                for (int i = 1; i < gameSnake.snake.size(); ++i)
                {
                    if (gameSnake.snake[i].y == snake_head_row_position)
                    {
                        gameSnake.snake[i].x --;
                    }
                    else if (gameSnake.snake[i].y > snake_head_row_position)
                    {
                        gameSnake.snake[i].y --;
                    }
                    else if (gameSnake.snake[i].y < snake_head_row_position)
                    {
                        gameSnake.snake[i].y ++;
                    }
                }
            }
        }
        break;
        case RIGHT:
        {
            if (gameSnake.snake[0].x < gameSnake.snake[1].x)
            {
                keepPlaying = false;
                break;
            }
            if(snake_head_col_position != 19)
            {
                snake_head_col_position ++;
                for (int i = 1; i < gameSnake.snake.size(); ++i)
                {
                    if (gameSnake.snake[i].y == snake_head_row_position)
                    {
                        gameSnake.snake[i].x ++;
                    }
                    else if (gameSnake.snake[i].y > snake_head_row_position)
                    {
                        gameSnake.snake[i].y --;
                    }
                    else if (gameSnake.snake[i].y < snake_head_row_position)
                    {
                        gameSnake.snake[i].y ++;
                    }
                }
            }
        }
        break;
        case STOP:
        {
            // start of the game, basically do nothing
        }
    }
    // this is misleading, but works (for now)
    // the origin is at the to-left, y axis is down
    
    // set the head position correctly
    // this can be handled in the for loop below
    board[snake_head_row_position][snake_head_col_position] = 'O';

    // update snake coordinates in the board
    for (int i = i; i < gameSnake.snake.size(); ++i)
    {
        int row = gameSnake.snake[i].y;
        int column = gameSnake.snake[i].x;
        board[row][column] = 'O';
    }

    // these should be member functions so that we don't have to call this every time
    std::default_random_engine generator(time(NULL));
    std::uniform_int_distribution<int> distribution(1, 18);
    
    if (snake_head_row_position == fruit1[0] && snake_head_col_position == fruit1[1])
    {
        // reroll fruit 1 and make sure it its not in the same position as fruit 2
        fruit1[0] = distribution(generator);
        fruit1[1] = distribution(generator);
        while(fruit1[0] == fruit2[0] && fruit1[1] == fruit2[1])
        {
            fruit1[0] = distribution(generator);
        }
        Position newPosition;
        int secondLastXPosition = gameSnake.snake[gameSnake.snake.size() - 2].x;
        int secondLastYPosition = gameSnake.snake[gameSnake.snake.size() - 2].y;

        int lastXPosition = gameSnake.snake[gameSnake.snake.size() - 1].x;
        int lastYPosition = gameSnake.snake[gameSnake.snake.size() - 1].y;

        // they are on the same x coordinate
        if (secondLastXPosition == lastXPosition)
        {
            newPosition.x = lastXPosition;
            if (secondLastYPosition > lastYPosition)
                newPosition.y = lastYPosition -1;
            else
                newPosition.y = lastYPosition + 1;
        }
        // if they are on the same y coordinate
        else if (secondLastYPosition == lastYPosition)
        {
            newPosition.y = lastYPosition;
            if (secondLastXPosition > lastXPosition)
                newPosition.x = lastXPosition - 1;
            else
                newPosition.x = lastXPosition + 1;
        }
        gameSnake.snake.push_back(newPosition);
    }
    else if (snake_head_row_position == fruit2[0] && snake_head_col_position == fruit2[1])
    {
        // reroll fruit 2 and make usre it is not in the same position as fruit 1
        fruit2[0] = distribution(generator);
        fruit2[1] = distribution(generator);
        while(fruit1[0] == fruit2[0] && fruit1[1] == fruit2[1])
        {
            fruit2[0] = distribution(generator);
        }

        Position newPosition;
        int secondLastXPosition = gameSnake.snake[gameSnake.snake.size() - 2].x;
        int secondLastYPosition = gameSnake.snake[gameSnake.snake.size() - 2].y;

        int lastXPosition = gameSnake.snake[gameSnake.snake.size() - 1].x;
        int lastYPosition = gameSnake.snake[gameSnake.snake.size() - 1].y;

        // they are on the same x coordinate
        if (secondLastXPosition == lastXPosition)
        {
            newPosition.x = lastXPosition;
            if (secondLastYPosition > lastYPosition)
                newPosition.y = lastYPosition -1;
            else
                newPosition.y = lastYPosition + 1;
        }
        // if they are on the same y coordinate
        else if (secondLastYPosition == lastYPosition)
        {
            newPosition.y = lastYPosition;
            if (secondLastXPosition > lastXPosition)
                newPosition.x = lastXPosition - 1;
            else
                newPosition.x = lastXPosition + 1;
        }
        gameSnake.snake.push_back(newPosition);
    }

    board[fruit1[0]][fruit1[1]] = 'X';
    board[fruit2[0]][fruit2[1]] = 'X';

    // make sure there are no overlapping snake cells
}

// Destructor
SnakeGame::~SnakeGame()
{
    delete[] fruit1;
    delete[] fruit2;
}