#include "tank.h"

Tank::Tank(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(cellSize, cellSize));
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

void Tank::draw(sf::RenderWindow& window) {
    window.draw(shape);
    path.draw(window); // Asegúrate de dibujar el camino también
}

void Tank::move(float offsetX, float offsetY) {
    shape.move(offsetX, offsetY);
}

void Tank::moveToPosition(const std::vector<std::pair<int, int>>& positions) { // Cambié el nombre del parámetro a "positions"
    if (positions.empty()) return;  
    
    // Limpiar el camino anterior
    path = Path(); // Reiniciar el camino

    for (const auto& position : positions) {
        float targetX = position.first * cellSize;
        float targetY = position.second * cellSize;

        // Agregar el punto al camino
        path.addPoint(sf::Vector2f(targetX, targetY));
        shape.setPosition(targetX, targetY);
    }
}

bool Tank::contains(float x, float y) const {
    return shape.getGlobalBounds().contains(x, y);
}

void Tank::select() {
    isSelected = true;
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color::Yellow);
}

void Tank::deselect() {
    isSelected = false;
    shape.setOutlineThickness(0);
}

sf::Vector2f Tank::getPosition() const {
    return shape.getPosition();
}
