// path.h
#ifndef PATH_H
#define PATH_H

#include <SFML/Graphics.hpp>
#include <vector>

class Path {
public:
    void addPoint(const sf::Vector2f& point);
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::Vertex> points; // Almacena los puntos del camino
};

#endif // PATH_H
