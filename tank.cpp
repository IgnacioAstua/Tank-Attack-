#include "tank.h"

Tank::Tank(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(cellSize, cellSize));
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
    if (path.empty()) return;  
    for (const auto& position : path) {
        float targetX = position.first * cellSize;
        float targetY = position.second * cellSize;
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
