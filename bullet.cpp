#include "bullet.h"
#include <cmath>

const float Bullet::speed = 600.0f; // Ajusta la velocidad según sea necesario

Bullet::Bullet(float x, float y, float targetX, float targetY) {
    shape.setRadius(5.0f); // Tamaño de la bala
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);

    // Calcula la dirección y normaliza
    direction = sf::Vector2f(targetX - x, targetY - y);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // Normaliza
}

void Bullet::update() {
    shape.move(direction * speed * 0.016f); // Multiplica por deltaTime si es necesario
}

void Bullet::draw(sf::RenderWindow& window) const { // Asegúrate de que sea const
    window.draw(shape);
}

bool Bullet::isOutOfBounds() const {
    return shape.getPosition().x < 0 || shape.getPosition().x > 800 || // Asumiendo un ancho de 800
           shape.getPosition().y < 0 || shape.getPosition().y > 600; // Asumiendo un alto de 600
}
