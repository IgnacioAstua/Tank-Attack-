#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>

class Tank {
public:
    Tank(float x, float y, sf::Color color);
    void draw(sf::RenderWindow& window);
    void move(float offsetX, float offsetY);
    bool contains(float x, float y) const;
    void select();
    void deselect();
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape shape;
    bool isSelected = false;
};

#endif
