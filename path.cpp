// path.cpp
#include "path.h"

void Path::addPoint(const sf::Vector2f& point) {
    points.push_back(sf::Vertex(point, sf::Color::Green)); // Color de la línea
}

void Path::draw(sf::RenderWindow& window) {
    if (points.size() > 1) {
        window.draw(&points[0], points.size(), sf::PrimitiveType::LinesStrip);
    }
}
