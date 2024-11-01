#include "bullet.h"
#include <cmath>

const float Bullet::speed = 300.0f;

Bullet::Bullet(float x, float y, float targetX, float targetY)
    : bounceCount(0) // Inicializa el contador de rebotes
{
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);

    direction = sf::Vector2f(targetX - x, targetY - y);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;
}

void Bullet::update() {
    shape.move(direction * speed * 0.016f); // Ajusta el tiempo según sea necesario

    // Verifica colisión con los bordes y rebota
    if (shape.getPosition().x < 0) {
        shape.setPosition(0, shape.getPosition().y);
        direction.x = -direction.x;
        bounceCount++; // Incrementa el contador de rebotes
    } else if (shape.getPosition().x > 800 - shape.getRadius() * 2) {
        shape.setPosition(800 - shape.getRadius() * 2, shape.getPosition().y);
        direction.x = -direction.x;
        bounceCount++;
    }

    if (shape.getPosition().y < 0) {
        shape.setPosition(shape.getPosition().x, 0);
        direction.y = -direction.y;
        bounceCount++;
    } else if (shape.getPosition().y > 600 - shape.getRadius() * 2) {
        shape.setPosition(shape.getPosition().x, 600 - shape.getRadius() * 2);
        direction.y = -direction.y;
        bounceCount++;
    }
}

bool Bullet::shouldRemove() const {
    return bounceCount >= 2; // Eliminar la bala después de 2 rebotes
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::CircleShape Bullet::getShape() const {
    return shape;
}
