#include "path.h"

// Constructor por defecto
Path::Path() {}

// Establecer un nuevo camino
void Path::setPath(const std::vector<std::pair<int, int>>& newPath) {
    pathLine.clear();  // Limpiar
    for (const auto& point : newPath) {
        // Añadir puntos al camino, escalados por el tamaño de celda
        pathLine.push_back(sf::Vertex(sf::Vector2f(point.first * cellSize, point.second * cellSize), sf::Color::Red));
    }
}

// Limpiar el camino actual
void Path::clear() {
    pathLine.clear();
}

// Dibujar el camino en la ventana
void Path::draw(sf::RenderWindow& window) {
    if (!pathLine.empty()) {
        window.draw(&pathLine[0], pathLine.size(), sf::LinesStrip);  // Dibujar la línea
    }
}
