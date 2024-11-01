#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y, float targetX, float targetY);
    void update();
    void draw(sf::RenderWindow& window) const;
    bool isOutOfBounds() const;
    sf::CircleShape getShape() const;
    bool shouldRemove() const; // Método para verificar si la bala debe eliminarse
private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    static const float speed;
    int bounceCount; // Contador de rebotes
};

#endif // BULLET_H
