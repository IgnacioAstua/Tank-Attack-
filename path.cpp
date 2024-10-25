#include "path.h"
#include <cmath>


// Constructor por defecto
Path::Path() {}

// Establecer un nuevo camino
void Path::setPath(const std::vector<std::pair<int, int>>& newPath) {
    pathLine.clear();  // Limpiar el camino previo
    for (const auto& point : newPath) {
        // Añadir puntos al camino, escalados por el tamaño de celda
        pathLine.push_back(sf::Vertex(sf::Vector2f(point.first * cellSize, point.second * cellSize), sf::Color::Red));
    }
}

// Limpiar el camino actual
void Path::clear() {
    pathLine.clear();
}

// Método para dibujar el camino como líneas gruesas
void Path::draw(sf::RenderWindow& window) {
    if (!pathLine.empty()) {
        for (size_t i = 0; i < pathLine.size() - 1; ++i) {
            sf::Vertex line[] = {
                pathLine[i],
                pathLine[i + 1]
            };
            // Crear un rectángulo entre los dos puntos
            sf::VertexArray rect(sf::Quads, 4);
            sf::Vector2f direction = line[1].position - line[0].position;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;  // Normalizar

            // Crear los vértices del rectángulo
            sf::Vector2f normal(direction.y, -direction.x);  // Perpendicular a la dirección
            float thickness = 5.0f;  // Cambia este valor para ajustar el grosor

            rect[0].position = line[0].position + normal * (thickness / 2);
            rect[1].position = line[0].position - normal * (thickness / 2);
            rect[2].position = line[1].position - normal * (thickness / 2);
            rect[3].position = line[1].position + normal * (thickness / 2);

            rect[0].color = line[0].color;
            rect[1].color = line[0].color;
            rect[2].color = line[1].color;
            rect[3].color = line[1].color;

            window.draw(rect);  // Dibujar el rectángulo
        }
    }
}

void Path::setColor(sf::Color color) {
    for (auto& vertex : pathLine) {
        vertex.color = color;  // Cambiar el color de cada vértice
    }
}