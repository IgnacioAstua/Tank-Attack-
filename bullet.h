#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y, float targetX, float targetY); // Solo los 4 parámetros
    void update();
    void draw(sf::RenderWindow& window) const; // Asegúrate de que sea const
    bool isOutOfBounds() const;

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    static const float speed; // Velocidad de la bala
};

#endif // BULLET_H
