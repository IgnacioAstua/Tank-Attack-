#include "tank.h"

// Constructor
Tank::Tank(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(30, 30)); // Tamaño del tanque
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

// Método para dibujar el tanque
void Tank::draw(sf::RenderWindow& window) {
    window.draw(shape);
    path.draw(window);  // Dibujar el camino recorrido por el tanque
}

// Método para mover el tanque por un desplazamiento
void Tank::move(float offsetX, float offsetY) {
    shape.move(offsetX, offsetY);
}

// Método para mover el tanque usando una ruta (BFS)
void Tank::moveToPosition(const std::vector<std::pair<int, int>>& path) {
    this->path.setPath(path);  // Establecer el nuevo camino
    shape.setPosition(path.back().first * cellSize, path.back().second * cellSize);
}

// Método para verificar si el tanque contiene el punto
bool Tank::contains(float x, float y) const {
    return shape.getGlobalBounds().contains(x, y);
}

// Seleccionar el tanque
void Tank::select() {
    isSelected = true;
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Yellow);
}

// Deseleccionar el tanque
void Tank::deselect() {
    isSelected = false;
    shape.setOutlineThickness(0);
}

// Obtener la posición actual del tanque
sf::Vector2f Tank::getPosition() const {
    return shape.getPosition();
}

// Limpiar el camino actual
void Tank::clearPath() {
    path.clear();  // Borra el camino almacenado
}
