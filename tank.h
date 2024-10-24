#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "path.h"  // Asegúrate de incluir la cabecera de Path

class Tank {
public:
    Tank(float x, float y, sf::Color color);
    void draw(sf::RenderWindow& window);
    void move(float offsetX, float offsetY);
    void moveToPosition(const std::vector<std::pair<int, int>>& path);
    bool contains(float x, float y) const;
    void select();
    void deselect();
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape shape;
    bool isSelected = false;
    static const int cellSize = 30; // Tamaño de cada celda en la cuadrícula
    Path path; // Añadir la variable Path aquí
};

#endif // TANK_H
