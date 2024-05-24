#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
public:
    Player(float width, float height, float screen_x, float screen_y);
    void move(int index, float offset_y);
    void setPosition(int index, float x, float y);
    std::vector<sf::RectangleShape>& getShapes();

private:
    std::vector<sf::RectangleShape> shapes;
    float screen_x;
    float screen_y;
    float width;
    float height;
};

#endif
