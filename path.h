#ifndef PATH_H
#define PATH_H

#include <SFML/Graphics.hpp>
#include <vector>

class Path {
public:
    // Constructor por defecto
    Path();

    // Establecer un nuevo camino
    void setPath(const std::vector<std::pair<int, int>>& newPath);

    // Limpiar el camino actual
    void clear();

    // Dibujar el camino en la ventana
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::Vertex> pathLine;  // Almacena los puntos del camino
    static const int cellSize = 30;  // Tamaño de cada celda
};

#endif // PATH_H
