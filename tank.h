#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "path.h"  

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
    void clearPath();
    
    void decideMovement(const std::vector<std::vector<int>>& grid, int targetX, int targetY); // Nueva función para decidir el movimiento

private:
    sf::RectangleShape shape;
    bool isSelected = false;
    static const int cellSize = 30; // Tamaño de cada celda en la cuadrícula
    Path path;

    std::vector<std::pair<int, int>> performBFS(const std::vector<std::vector<int>>& grid, int startX, int startY, int targetX, int targetY); // Declaración de BFS
    std::vector<std::pair<int, int>> performRandomMovement(const std::vector<std::vector<int>>& grid, int startX, int startY); // Declaración del movimiento aleatorio
    bool isPositionValid(int x, int y, const std::vector<std::vector<int>>& grid); // Verificar si la posición es válida
};

#endif // TANK_H
