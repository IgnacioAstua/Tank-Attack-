#include "tank.h"

Tank::Tank(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(30, 30)); // Tamaño del tanque
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

void Tank::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Tank::move(float offsetX, float offsetY) {
    shape.move(offsetX, offsetY);
}

void Tank::moveToPosition(const std::vector<std::pair<int, int>>& path) {
    if (!path.empty()) {
        for (const auto& position : path) {
            float newX = position.first * cellSize;  // Convertir coordenadas de la cuadrícula a píxeles
            float newY = position.second * cellSize;
            shape.setPosition(newX, newY);  // Mover el tanque a la nueva posición
            
        }
    }
}


       
bool Tank::contains(float x, float y) const {
    return shape.getGlobalBounds().contains(x, y);
}

void Tank::select() {
    isSelected = true;
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::Yellow); // Cambiar el borde para indicar selección
}

void Tank::deselect() {
    isSelected = false;
    shape.setOutlineThickness(0);
}

sf::Vector2f Tank::getPosition() const {
    return shape.getPosition();
}
